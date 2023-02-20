#include "ssh_session.h"

using namespace std;

int main(int argc, char** argv)
{
    cout << "test 1" << endl;
    SSH_session session1("192.168.1.1", "root", PASSWORD, "root");

    session1.connect();
   
    printf("executing command\n");
    cout << session1.exec("echo Hello World") << endl;

    printf("disconnecting\n");
    session1.disconnect();


    cout << "test 2" << endl;

    SSH_session session2("192.168.1.1", "root", PASSWORD, "root");

    session2.connect();

    SSH_channel ch1 = session2.get_channel();

    SSH_channel ch2 = session2.get_channel();


    cout << ch1.exec("echo HELLO WORLD ON CHANNEL 1") << endl;

    cout << ch2.exec("echo HELLO WORLD ON CHANNEL 2") << endl;

    ch1.close();
    ch2.close();


}