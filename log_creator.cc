#include <iostream>
#include <cstdio>
#include <unistd.h>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include "shmringbuffer.hh"

struct LogNode {
    int ts;  // timestamp
    int len; // length
#define MAX_LOG_LEN 256000
    char log[MAX_LOG_LEN];
    long int times;
    char appid[4 + 1];
    char level[7 + 1];


    const std::string unparse() {
        return "[" + std::to_string(ts) + "] " + std::string(&log[0]);
    }
};

int main()
{
    /* initialize random seed: */
    srand (time(NULL));

    const int CAPACITY = 20;
    {
        ShmRingBuffer<LogNode> buffer(CAPACITY, true);
        int start = 2000;
        LogNode log;
        while (1) {
            for (int i = start; i < start + 10*CAPACITY; ++i){
                snprintf(log.log, MAX_LOG_LEN, "%zu: %d", buffer.end(), i);
                //std::cout<<"log.log is "<<log.log<<std::endl;
                buffer.push_back(log);
                std::cout << "log creator: " << i << ", index " << buffer.end() << std::endl;
                usleep(1000000);
            }

        }
    }

    return 0;
}
