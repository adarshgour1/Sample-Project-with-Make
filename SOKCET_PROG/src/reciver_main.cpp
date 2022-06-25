#include "socket_function.hpp"


int main()
{
    setvbuf(stdout, NULL, _IOFBF, 0); //full buffering

    signal(SIGINT, signalHandler);
    signal(SIGTERM, signalHandler);
    signal(SIGKILL, signalHandler);

    int fdServSock = get_reciver_socket_fd();
    int i;
    while (read(fdServSock, &i, sizeof(int)))
    {
        Log << "Recive Data i:[" << i << "]";
    }

    Log << "All data recived";
    Log << "Process completed it work";
    close(fdServSock);
    return 0;
}