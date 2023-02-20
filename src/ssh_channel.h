#ifndef DEF_SSH_CHANNEL
#define DEF_SSH_CHANNEL

#include <libssh/libssh.h>
#include <iostream>
#include <string>

using namespace std;

class SSH_session;

class SSH_channel {

private:
    ssh_session &session;

    ssh_channel channel;

    bool isOpen;

public:
    /**
     * @brief Construct a new ssh channel object
     * 
     * @param session_ the linked session
     */
    SSH_channel(ssh_session &session_);

    /**
     * @brief open the channel to the server
     * 
     * @return true 
     * @return false 
     */
    bool open();

    /**
     * @brief close the channel with the server
     * 
     */
    void close();


    /**
     * @brief executes command
     * 
     * @param command command to execute
     * @return string returns the result
     */
    string exec(string command, unsigned int bufferSize = 1024);



};

#endif