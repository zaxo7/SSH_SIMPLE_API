#include "ssh_channel.h"

SSH_channel::SSH_channel(ssh_session &session_) : session(session_), channel(NULL), isOpen(false)
{
    channel = ssh_channel_new(session);
    if (channel == NULL) {
        cerr << "Error creating channel: " << ssh_get_error(session) << endl;
        ssh_disconnect(session);
        ssh_free(session);
        session = NULL;
        exit(-1);
    }



}

bool SSH_channel::open()
{
    int rc = ssh_channel_open_session(channel);
    if (rc != SSH_OK) {
        fprintf(stderr, "Error opening channel: %s\n", ssh_get_error(session));
        ssh_channel_free(channel);
        ssh_disconnect(session);
        ssh_free(session);
        session = NULL;
        return false;
    }

    isOpen = true;

    return true;
}

void SSH_channel::close()
{
    if(isOpen && channel)
    {
        ssh_channel_close(channel);
        ssh_channel_free(channel);
    }
    isOpen = false;
}

string SSH_channel::exec(string command, unsigned int bufferSize)
{
    string result;
    // Execute a command
    int rc = ssh_channel_request_exec(channel, command.c_str());
    if (rc != SSH_OK) {
        fprintf(stderr, "Error executing command: %s\n", ssh_get_error(session));
        ssh_channel_close(channel);
        ssh_channel_free(channel);
        ssh_disconnect(session);
        ssh_free(session);
        session = NULL;
        return "";
    }

    char* buffer = (char*)malloc(bufferSize);

    // Read the output
    int nbytes;
    do
    {
        nbytes = ssh_channel_read(channel, buffer, bufferSize, 0);
        result += buffer;
    }while(nbytes != -1);
    

    ssh_channel_send_eof(channel);


    return result;
}