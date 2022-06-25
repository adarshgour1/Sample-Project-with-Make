#ifndef __SOCKET_FUNCTION_HPP
#define __SOCKET_FUNCTION_HPP

#include "common_header.hpp"
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <error.h>
#include <errno.h>
#include <unistd.h>

#define PORT_NUM 12345
#define LISTEN_OPT 3
#define ADDRESS "127.0.0.1"

int get_sender_socket_fd();
int get_reciver_socket_fd();
void signalHandler(int sig);

#endif