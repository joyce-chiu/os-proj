#ifndef JOB_H
#define JOB_H

class Job {
public:
    int job_num;
    int priority;
    int size;
    int maxTime;
    int enterTime;
    int currTime;
    int address;
    bool inMem;
    bool doingIO;
    bool requestingIO;
    bool swapping;
    bool running;
	
    Job::Job() {
        job_num = -1;
        priority = -1;
        size = 0 ;
        maxTime = -1;
        currTime = -1;
        address = -1;
        inMem = false;
        doingIO = false;
        requestingIO = false;
        swapping = false;
        running = false;
    }
    Job::Job( int num, int priority, int size, int max_time , int curr_time){
        job_num = num;
        priority = priority;
        size = size;
        maxTime = max_time;
        enterTime = curr_time;
        address = -1 ;
        inMem = false;
        doingIO = false;
        requestingIO = false;
        swapping = false;
        running = false;
    }
};

#endif // JOB_H
