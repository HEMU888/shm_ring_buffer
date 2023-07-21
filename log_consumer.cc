#include <iostream>
#include <cstdio>
#include <unistd.h>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include "shmringbuffer.hh"

struct LogNode
{
    int ts;  // timestamp
    int len; // length
#define MAX_LOG_LEN 256000
    char log[MAX_LOG_LEN];

    const std::string unparse()
    {
        return "[" + std::to_string(ts) + "] " + std::string(&log[0]);
    }
};

int main()
{
    /* initialize random seed: */
    srand(time(NULL));

    const int CAPACITY = 20;

    {
        // child process
        // usleep(500);
        ShmRingBuffer<LogNode> buffer(CAPACITY, false);
        LogNode log;
        int i = buffer.begin();
        while (1)
        {
            if (i != buffer.end())
            {
                log = buffer.pop(i);
                i = (i + 1) % buffer.capacity();
                std::cout << "log consumer:" << log.log << std::endl;
            }
            else
            {
                usleep(2000000);
            }
        }
    }

    return 0;
}
