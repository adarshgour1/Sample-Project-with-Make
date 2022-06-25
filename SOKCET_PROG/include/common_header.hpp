#ifndef __ADARSH_HPP
#define __ADARSH_HPP

#include <iostream>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
using namespace std;

// if you want to turn off logging and just want
// to print simple print statement ucomment following line
// #define PRODUCTION_SERVER

#ifndef PRODUCTION_SERVER
//for C language
#define LogDebug(msg, ...)                           \
    fprintf(stdout, "#%d:%s\n", __LINE__, __FILE__); \
    fprintf(stdout, "DEBUG:%s::" msg " \n", get_time_stamp(), ##__VA_ARGS__);

//for C++ language
#define Log                                                   \
    std::cout << "\n#" << __LINE__ << ":" << __FILE__ << "\n" \
              << "DEBUG:" << get_time_stamp() << ":: "
#else
#define LogDebug(msg, ...) \
    fprintf(stdout, msg "\n", ##__VA_ARGS__);

#define Log std::cout << "\n"
#endif

char *get_time_stamp();

#endif
