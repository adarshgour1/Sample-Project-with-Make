#include "socket_function.hpp"

int main()
{
    setvbuf(stdout, NULL, _IOFBF, 0); //full buffering
    signal(SIGINT, signalHandler);
    signal(SIGTERM, signalHandler);
    signal(SIGKILL, signalHandler);

    int fdSockCli = get_sender_socket_fd();

    for (int i = 0; i < 1000; i++)
    {
        Log << "Sending i:[" << i << "]";
        if (send(fdSockCli, (char *)&i, sizeof(int), 0) == -1)
        {
            Log << "error while sending data: [" << errno << "] :: " << strerror(errno);
            break;
        }
    }
    Log << "All data sent";
    Log << "Process completed it work";
    close(fdSockCli);

    return 0;
}