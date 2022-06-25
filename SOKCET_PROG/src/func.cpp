#include "socket_function.hpp"

char *get_time_stamp()
{
    char stamp[9];
    struct timeval tv;
    static char _gtime[16];
    gettimeofday(&tv, NULL);
    strftime(stamp, 20, "%H:%M:%S", localtime(&tv.tv_sec));
    sprintf(_gtime, "%s.%06ld", stamp, tv.tv_usec);
    return _gtime;
}

/**
 * @brief Listen for client to connect as any connection is made
 * return fd for that connection. 
 * 
 * @return int 
 */
int get_sender_socket_fd()
{
    int fdSocket, iRetVal;
    int opt = 1;
    struct sockaddr_in oSockAddr;

    int fdSocketCli;
    struct sockaddr_in oCliSockAddr;
    socklen_t uiSockAddressLen;

    //creating a socket
    fdSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (fdSocket == -1)
    {
        Log << "error while creating socket: [" << errno << "] :: " << strerror(errno);
        exit(EXIT_FAILURE);
    }
    Log << "socket created successfully with socket id: [" << fdSocket << "]";

    //Forcefully setting option to reuse Port and address
    iRetVal = setsockopt(fdSocket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
    if (iRetVal == -1)
    {
        Log << "error while setting socket option: [" << errno << "] :: " << strerror(errno);
        exit(EXIT_FAILURE);
    }
    Log << "socket option set successfully";

    //setting socket option
    oSockAddr.sin_family = AF_INET;
    oSockAddr.sin_addr.s_addr = INADDR_ANY;
    oSockAddr.sin_port = htons(PORT_NUM);

    //binding socket
    iRetVal = bind(fdSocket, (sockaddr *)&oSockAddr, sizeof(oSockAddr));
    if (iRetVal == -1)
    {
        Log << "error while binding socket: [" << errno << "] :: " << strerror(errno);
        exit(EXIT_FAILURE);
    }
    Log << "socket bind successfully";

    //listing on socket
    iRetVal = listen(fdSocket, LISTEN_OPT);
    if (iRetVal == -1)
    {
        Log << "error while listing on socket: [" << errno << "] :: " << strerror(errno);
        exit(EXIT_FAILURE);
    }
    Log << "socket listing ...";

    //Waiting for client to connect
    fdSocketCli = accept(fdSocket, (sockaddr *)&oCliSockAddr, &uiSockAddressLen);
    if (fdSocketCli == -1)
    {
        Log << " error on accepting connection : [" << errno << "] :: " << strerror(errno);
        exit(EXIT_FAILURE);
    }
    Log << "Client is connected with socket id [" << fdSocketCli << "]";
    return fdSocketCli;
}

void signalHandler(int sig)
{
    Log << "Signal is Caught: [" << sig << "]";
    Log << "System going down...";
    exit(sig);
}

/**
 * @brief conncet to server as connection is made
 * return fd for that connection. 
 * 
 * @return int 
 */
int get_reciver_socket_fd()
{
    int fdSocket, iRetVal;
    struct sockaddr_in oSockAddr;

    //creating a socket
    fdSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (fdSocket == -1)
    {
        Log << "error while creating socket: [" << errno << "] :: " << strerror(errno);
        exit(EXIT_FAILURE);
    }
    Log << "socket created successfully with socket id: [" << fdSocket << "]";

    //setting socket option
    oSockAddr.sin_family = AF_INET;
    oSockAddr.sin_port = htons(PORT_NUM);
    iRetVal = inet_pton(AF_INET, ADDRESS, &oSockAddr.sin_addr);
    if (iRetVal == -1)
    {
        Log << "error while inet_pton: [" << errno << "] :: " << strerror(errno);
        exit(EXIT_FAILURE);
    }

    iRetVal = connect(fdSocket, (sockaddr *)&oSockAddr, sizeof(oSockAddr));
    if (iRetVal == -1)
    {
        Log << "error while connect: [" << errno << "] :: " << strerror(errno);
        exit(EXIT_FAILURE);
    }
    Log << "connected to server ...";
    return fdSocket;
}