#include "../src/ssh_session.h"


int main(int argc, char** argv)
{
    SSH_session session1("github.com", "root", PUBKEY, "root");

    session1.connect();
}