#ifndef JOB_H
#define JOB_H

class Job {
public:
    int job_num;
    int jobPriority;
    int jobSize;
    int maxTime;        //Max CPU time
    int enterTime;      //Time when job begins using the CPU
    int jobAddress;
    bool inMem;
    bool doingIO;
    bool requestingIO;
    bool swapping;
    bool running;
    bool killed;
    bool blocked;


    Job() {
        job_num = -1;
        jobPriority = -1;
        jobSize = 0 ;
        maxTime = -1;
        enterTime = -1;
        jobAddress = -1;
        inMem = false;
        doingIO = false;
        requestingIO = false;
        swapping = false;
        running = false;
        killed = false;
        blocked = false;
    }

    Job( int num, int priority, int size, int max_time , int current_time){
        job_num = num;
        jobPriority = priority;
        jobSize = size ;
        maxTime = max_time;
        enterTime = current_time;
        jobAddress = -1 ;
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
