#include "../src/ssh_session.h"

using namespace std;

int main(int argc, char** argv)
{
    SSH_session session1("192.168.1.1", "root", PASSWORD, "root");

    if(session1.connect())
    {
        printf("executing command\n");
        cout << session1.exec("echo Hello World") << endl;

        printf("disconnecting\n");
        session1.disconnect();
    }
    else
    {
        cout << "can't connect" << endl;
    }
}