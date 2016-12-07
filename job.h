#ifndef JOB_H
#define JOB_H

class Job {
public:
    int job_num;
    int priority;
    int size;
    int maxTime;        //Max CPU time
    int enterTime;      //Time when job begins using the CPU
    int address;
    bool inMem;
    bool doingIO;
    bool requestingIO;
    bool swapping;
    bool running;
    bool killed;
    bool blocked;

	
    Job::Job() {
        job_num = -1;
        priority = -1;
        size = 0 ;
        maxTime = -1;
        enterTime = -1;
        address = -1;
        inMem = false;
        doingIO = false;
        requestingIO = false;
        swapping = false;
        running = false;
        killed = false;
        blocked = false;
    }
    Job::Job( int num, int priority, int size, int max_time , int current_time){
        job_num = num;
        priority = priority;
        size = size ;
        maxTime = max_time;
        enterTime = current_time;
        address = -1 ;
        inMem = false;
        doingIO = false;
        requestingIO = false;
        swapping = false;
        running = false;
        killed = false;
        blocked = false;
    }
};

#endif // JOB_H
