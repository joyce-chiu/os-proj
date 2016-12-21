#ifndef JOB_H
#define JOB_H

class Job {
private:
    long  jobNum;
    long  jobPriority;
    long  jobSize;
    long  maxTime;        //Max CPU time
    long  enterTime;      //Time when job begins using the CPU
    long  jobAddress;
    long  jobStartLoc;
    long  jobEndLoc;
    bool inMem;
    bool doingIO;
    bool requestingIO;
    bool swapping;
    bool running;
    bool killed;
    bool blocked;

public:
    Job() {
        jobNum = -1;
        jobPriority = -1;
        jobSize = 0 ;
        maxTime = -1;
        enterTime = -1;
        jobAddress = -1;
        jobStartLoc = -1;
        jobEndLoc = -1;
        inMem = false;
        doingIO = false;
        requestingIO = false;
        swapping = false;
        running = false;
        killed = false;
        blocked = false;
    }

    Job( long  job_num, long  priority, long  job_size, long  max_time , long  current_time){
        jobNum = job_num;
        jobPriority = priority;
        jobSize = job_size ;
        maxTime = max_time;
        enterTime = current_time;
        jobAddress = -1 ;
        jobStartLoc = -1;
        jobEndLoc = -1;
        inMem = false;
        doingIO = false;
        requestingIO = false;
        swapping = false;
        running = false;
        killed = false;
        blocked = false;
    }
    long getJobNum(){
    	return jobNum;
    }

    long  getjobPriority(){
    	return jobPriority;
    }


    long  getJobSize(){
    	return jobSize;
    }

    void setJobSize(long  jobSize){
    	this -> jobSize = jobSize;
    }

    long  getMaxTime(){
    	return maxTime;
    }

    void setMaxTime(long  maxTime){
    	this ->maxTime = maxTime;
    }

    long  getEnterTime(){
    	return enterTime;
    }

    void setEnterTime(long enterCPUTime){
    	this ->enterTime = enterCPUTime;
    }

    long getJobStartLoc(){
        return jobStartLoc;
    }

    void setJobStartLoc(long startLoc){
        this -> jobStartLoc = startLoc;
    }

    long getJobEndLoc(){
        return jobEndLoc;
    }

    void setJobEndLoc(long endLoc){
        this -> jobEndLoc = endLoc;
    }


    bool getInMem(){
    	return inMem;
    }

    void setInMem(bool inMemory){
    	this -> inMem = inMemory;
    }

    long getJobAddress(){
    	return jobAddress;
    }

    void setjobAddress(long  address){
    	this -> jobAddress = address;
    }


    bool getDoingIO(){
    	return doingIO;
    }

    void setDoingIO(bool doingIO){
    	this->doingIO = doingIO;
    }

    bool getRequestingIO(){
    	return requestingIO;
    }

    void setRequestingIO(bool requestIO){
    	this->requestingIO = requestIO;
    }

    bool getSwapping(){
    	return swapping;
    }

    void setSwapping(bool swapping){
    	this->swapping = swapping;
    }

    bool getBlocked(){
    	return blocked;
    }

    void setBlocked(bool blocked){
    	this->blocked = blocked;
    }

    bool getRunning(){
    	return running;
    }

    void setRunning(bool running){
    	this->running = running;
    }

    bool getKilled(){
    	return killed;
    }

    void setKilled(bool killed){
    	this->killed = killed;
    }

};

#endif // JOB_H
