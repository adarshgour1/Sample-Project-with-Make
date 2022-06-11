#include "common_header.hpp"

void get_time_stamp()
{
    char stamp[9];
    struct timeval tv;

    gettimeofday(&tv, NULL);
    strftime(stamp, 20, "%H:%M:%S", localtime(&tv.tv_sec));
    sprintf(_gtime, "%s.%06ld", stamp, tv.tv_usec);
}
