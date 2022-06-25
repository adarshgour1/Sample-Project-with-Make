#ifndef __ADARSH_HPP
#define __ADARSH_HPP

#include <iostream>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>

// if you want to turn off logging and just want
// to print simple print statement ucomment following line
// #define PRODUCTION_SERVER

extern short ptr;

#ifndef PRODUCTION_SERVER

    // for C language
    #define LogDebug(msg, ...)                           \
        fprintf(stdout, "#%d:%s\n", __LINE__, __FILE__); \
        fprintf(stdout, "DEBUG:%s:" msg " \n", get_time_stamp(), ##__VA_ARGS__);

    // for C++ language
    #define Log0                                                  \
        if (ptr >= 0)                                            \
        std::cout << "\n#" << __LINE__ << ":" << __FILE__ << "\n" \
                << "DEBUG0:" << get_time_stamp() << ": "

    #define Log1                                                  \
        if (ptr >= 1)                                            \
        std::cout << "\n#" << __LINE__ << ":" << __FILE__ << "\n" \
                << "DEBUG1:" << get_time_stamp() << ": "
#else
    #define LogDebug(msg, ...) \
        fprintf(stdout, msg "\n", ##__VA_ARGS__);

    #define Log0\
    if (ptr >= 0)       \
            std::cout \
        << "\n"
    
    #define Log1\
    if (ptr >= 1)       \
            std::cout \
        << "\n"

#endif //PRODUCTION_SERVER

char *get_time_stamp();

#endif
