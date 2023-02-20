#include "ssh_session.h"

SSH_session::SSH_session(string _ip, string _username, AuthType auth, string key, unsigned int _port) :
SSH_session(_ip, _username, _port)
{
    authType = auth;

    if(auth == PUBKEY)
        pubkey = key;
    else
        password = key;
}

SSH_session::SSH_session(string _ip, string _username, unsigned int _port) :
SSH_session()
{
    ip = _ip;
    username = _username;
    port = _port;
}

SSH_session::SSH_session()
{
    session = ssh_new();
    if (session == NULL)
        cerr << "can't init the ssh session" << endl;
}

bool SSH_session::connect()
{
    //< disconnect old session
    if(session && (ssh_get_status(session) != SSH_CLOSED && ssh_get_status(session) != SSH_CLOSED_ERROR))
    {
        ssh_disconnect(session);
    }

    if(!session)
        return false;


    ssh_options_set(session, SSH_OPTIONS_HOST, ip.c_str());
    ssh_options_set(session, SSH_OPTIONS_PORT, &port);
    ssh_options_set(session, SSH_OPTIONS_USER, username.c_str());

    //ssh_options_set(session, SSH_OPTIONS_LOG_VERBOSITY, SSH_LOG_PROTOCOL);

    // Connect to the server
    int rc = ssh_connect(session);
    if (rc != SSH_OK) {
        cerr << "Error connecting to server: " << ssh_get_error(session) << endl;
        ssh_free(session);
        session = NULL;
        return false;
    }
    else
        cout << "connected..." << endl;


    // Authenticate
    if(authType == PASSWORD)
        rc = ssh_userauth_password(session, NULL, password.c_str());
    else
    {
        cerr << "error PUBLIC KEY auth not implemented yet" << endl;
        return false;
    }

    if (rc != SSH_AUTH_SUCCESS) {
        cerr << "Error authenticating " << ssh_get_error(session) << endl;
        ssh_disconnect(session);
        ssh_free(session);
        session = NULL;
        return false;
    }

    return true;
}

void SSH_session::disconnect()
{
    if(!session)
        return;

    ssh_disconnect(session);
    ssh_free(session);
    session = NULL;
}

string SSH_session::exec(string command, unsigned int bufferSize)
{
    if(!session)
        return "";

    char *buffer = (char*)malloc(bufferSize);
    // Open a channel
    ssh_channel channel = ssh_channel_new(session);
    if (channel == NULL) {
        cerr << "Error creating channel: " << ssh_get_error(session) << endl;
        ssh_disconnect(session);
        ssh_free(session);
        session = NULL;
        return "";
    }

    int rc = ssh_channel_open_session(channel);
    if (rc != SSH_OK) {
        fprintf(stderr, "Error opening channel: %s\n", ssh_get_error(session));
        ssh_channel_free(channel);
        ssh_disconnect(session);
        ssh_free(session);
        session = NULL;
        return "";
    }

    // Execute a command
    rc = ssh_channel_request_exec(channel, command.c_str());
    if (rc != SSH_OK) {
        fprintf(stderr, "Error executing command: %s\n", ssh_get_error(session));
        ssh_channel_close(channel);
        ssh_channel_free(channel);
        ssh_disconnect(session);
        ssh_free(session);
        session = NULL;
        return "";
    }

    // Read the output
    int nbytes = ssh_channel_read(channel, buffer, bufferSize, 0);


    ssh_channel_send_eof(channel);
    ssh_channel_close(channel);
    ssh_channel_free(channel);
    
    if(nbytes > 0)
        return string(buffer);
    else
        return "";
}

SSH_channel SSH_session::get_channel()
{
    // Open a channel
    SSH_channel chan(session);

    return chan;
}

//---------- setters and getters

void SSH_session::setUsername(string _username)
{
    if(username == _username)
        return;
    username = _username;
}

void SSH_session::setIp(string _ip)
{
    if(ip == _ip)
        return;
    ip = _ip;
}

void SSH_session::setPort(unsigned int _port)
{
    if(port == _port)
        return;
    port = _port;
}

void SSH_session::setPassword(string _password)
{
    if(password == _password)
        return;
    password = _password;
}

void SSH_session::setPubkey(string _pubkey)
{
    if(pubkey == _pubkey)
        return;
    pubkey = _pubkey;
}


SSH_session::~SSH_session()
{
    ///< erase sensitive data to avoid data leak
    ip = "";
    username = "";
    password = "";
    pubkey = "";

    if(session)
    {
        ssh_disconnect(session);
        ssh_free(session);
    }
}