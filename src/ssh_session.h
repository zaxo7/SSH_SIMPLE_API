#include <libssh/libssh.h>
#include <iostream>
#include <string>

using namespace std;

enum AuthType {
    PASSWORD,
    PUBKEY
};

class SSH_session {

private:
    string ip;
    string username;
    string password;
    string pubkey;
    unsigned int port;

    AuthType authType;

    ssh_session session;

public:

    /**
    * @brief Construct a new ssh session object
    * 
    * @param _ip server ip
    * @param _username auth username
    * @param type authentification type
    * @param key password or public key
    * @param _port server port
    */
    SSH_session(string _ip, string _username, AuthType type, string key, unsigned int _port = 22);

    /**
    * @brief Construct a new ssh session::ssh session object
    * 
    * @param _ip server ip
    * @param _username auth username
    * @param _port server port
    */
    SSH_session(string _ip, string _username, unsigned int _port = 22);

    /**
    * @brief Construct a new ssh session object
    * 
    */
    SSH_session();

    /**
     * @brief open the connection and authenticate with the server
     * 
     * @return true on success
     * @return false on failure
     */
    bool connect();

    /**
     * @brief disconnects from server
     * 
     */
    void disconnect();

    /**
     * @brief quickly execute a command and get the result
     * 
     * @param command 
     * @param bufferSize the size of the buffer for reading output
     * @return string 
     */
    string exec(string command, unsigned int bufferSize = 1024);

    //---------- setters and getters

    /**
    * @brief Set the Username object
    * 
    * @param _username 
    */
    void setUsername(string _username);

    /**
    * @brief Set the Ip object
    * 
    * @param _ip 
    */
    void setIp(string _ip);

    /**
    * @brief Set the Port object
    * 
    * @param _port 
    */
    void setPort(unsigned int _port);

    /**
    * @brief Set the Password object
    * 
    * @param _password 
    */
    void setPassword(string _password);

    /**
    * @brief Set the Pubkey object
    * 
    * @param _pubkey 
    */
    void setPubkey(string _pubkey);

    /**
    * @brief Destroy the ssh session object
    * 
    */
    ~SSH_session();




};