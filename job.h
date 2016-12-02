#ifndef JOB_H
#define JOB_H

class Job {
public:
    int job_num;
    int priority;
    int size;
    int maxTime;
    int curr_time;
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
        curr_time = -1;
        address = -1;
        inMem = false;
        doingIO = false;
        requestingIO = false;
        swapping = false;
        running = false;
    }
    Job::Job( int num, int priority, int size, int max_time , int current_time){
        job_num = num;
        priority = priority;
        size = size ;
        maxTime = time;
        curr_time = current_time;
        address = -1 ;
        inMem = false;
        doingIO = false;
        requestingIO = false;
        swapping = false;
        running = false;
    }
};

#endif // JOB_H
