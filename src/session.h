#ifndef DEF_SESSION
#define DEF_SESSION

class SESSION {

private:
    bool isConnected;
    
public:

    bool connect();

    void disconnect();
};



#endif