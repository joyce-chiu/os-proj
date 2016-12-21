#include <iostream>
#include <list>
#include<queue>
#include "job.h"   // include the job class
#include "memorymanager.h" // inludes the memory manager class

using namespace std;

static bool CurrentlySwapping;
static bool processingIO;

static queue <long > IOQ; // jobs waiting for I/O
//static const <Job>:: iterator IOjob = IOQ.front(); // iterator lock on to the front of the DEQUE, for easy access to the first element. Only first element is allowed to do i/o.

static list <Job> JobTable; //should be intialized with space for 50 jobs
static list<Job>::iterator job = JobTable.begin(); // A gloabl joberator for the job table. iterator points to the job object in the list.

static const long  timeSlice = 5; //in miliseconds

static MemoryManager memory;  // creates 100k of memory
static long runningJobNum;
static long IOJobNum;
//static long interruptedJobNum;
static long lastRunningJob = 0;
static long timeRemain = -1;

//Function Prototypes
void siodisk(long);
void siodrum(long jnum, long jsize, long jaddress, long direction);
void ontrace();
void offtrace();
void terminateJob(long jnum);
void swapper();
void runJob(long &a, long p[]);
void runIO();
list<Job>::iterator findRunningJob(long);
list<Job>::iterator findIOJob(long);
list<Job>::iterator findInterruptedJob(long);
long  findJobTablePos(long);
void bookkeeper(long);
void terminateJob(long);
Job jobObj(long);


void startup (){
    ontrace();
    CurrentlySwapping = false;
    processingIO = false;
}

void Crint (long &a, long p[]) {		//A new job has arrived, information about the job is in array p.

        cout << "Crint Initiated." << endl;

        bookkeeper(p[5]);

        /* 	    p[1] = job number
                p[2] = address
                p[3] = job size
                p[4] = max time
                p[5] = current time
        */

        if(JobTable.size() < 50) {
                Job *j = new Job(p[1], p[2], p[3], p[4], p[5]);
                JobTable.push_back(*j);// removed "new keyword. It wa giving compilation error"
                cout << "Crint completed." << endl;
        }
        else cout << "JobTable is full." << endl;

        runJob(a,p);
        return;
}

void Svc (long &a, long p[]) {

        cout << "SVC Initiated." << endl;

        bookkeeper(p[5]);
        while (job -> getJobNum()!= p[1]){ job++; }

        /*	If a = 5: the job is requesting termination.
                If a = 6: the job is requesting another disk I/O operation.
                If a = 7: the job requesting to be blocked until all pending I/O requests are completed.
        */

        if(a == 5) {    // a is not an array but a regualr int.

                cout << "SVC 5: Job requesting termination..." << endl;

                //Set killed bit of job to true if job is not doing I/O
                if(job->getDoingIO() == false)
                        job->setKilled(true);

                //Finally, terminate the job if kill bit is true
                if(job->getKilled() == true)
                        terminateJob(p[1]);

        }

        if(a == 6) {    // a is not an array but a regualr int.

                cout << "SVC 6: Job requesting another I/O disk operation..." << endl;

                //Set the requestingIO variable to true
                job->setRequestingIO(true);

                //Add the job number to the IO queue
                IOQ.push(job->getJobNum()); // queue is a FIFO structure. be default push(),adds to the end of the queue

                //Check if it is the only job on the queue
                //Check if system is already doing I/O
                //If not, start IO on job requesting IO
                if( (IOQ.size() == 1) && (processingIO == false)){
                        processingIO = true;
                        runIO();
                        
                }

        }

        if(a == 7) {    // a is not an array but a regualr int.

                cout << "SVC 7: Job requesting to be blocked until all of its pending I/O requests are completed..." << endl;

                //Set blocked bit of job to true if job is requesting for I/O
                if(job->getRequestingIO ()){
                        job->setBlocked(true);
              //  else job->setBlocked (false);
                        IOQ.push(job->getJobNum());
                }
        }

        cout << "SVC completed." << endl;
      //  runIO();

        runJob(a,p);
        return;
}


long CPU_scheduler () {

        //Select the next job to use the CPU and return the job number
        //The job is selected only if it is not blocked
        //If there are no more jobs on the job table, return -1


        cout << "CPU scheduler working." << endl;
        while ( lastRunningJob >= job -> getJobNum()){ job++; }//makes sure the next job is in table is shecduled. ROUND ROBIN. Each job gets 5s.
        long scheduledJob;	// Integer variable to hold the job number to use the CPU

        if (!JobTable.empty()){
            scheduledJob = job->getJobNum();
            job++;
            cout << "Scheduler completed. JOB SCHEDULED: " <<scheduledJob << endl;
            return scheduledJob;
        } else return -1;
}


void bookkeeper(long currentTime) {

        //This function calculates how much time the job spent on the CPU before it was interrupted and saves the new getMaxTime() of the job

        //long timeElapsed = currentTime - job->getEnterTime();
        long timeRemain = job->getMaxTime() - currentTime;

        job->setMaxTime(timeRemain);

        return;
}


void terminateJob(long jnum){

        memory.removeFromMemory((findInterruptedJob(jnum))->getJobStartLoc(), (findInterruptedJob(jnum))->getJobEndLoc());

        //Change inMem variable of job to false
        job ->setInMem(false);

        //Remove job from job table
        JobTable.erase(job);

        cout << "Job terminated." << endl;

        return;
}


void Drmint ( long &a, long p [] ){
     cout << "DRUM INTERRUPT" << endl << "Swap has finished. Setting flags." << endl;
        /*  Drum has finished swapping a job into of memory.  */

    /*  update swapped job in the job table
       Loop through job table looking for the job that was set to swap and reset flags
      */
    CurrentlySwapping = false;
    for( job = JobTable.begin(); job != JobTable.end(); ++job ){
           if (  job->getSwapping() ) {
                job->setSwapping(false);
                job->setInMem(true);
               // job ->setBlocked(false);
             //   break; // Once job info is updated, stop iterating through list.
           }
    }
    runJob(a,p);
}

void Tro ( long &a, long p [] ){

/*  if  a job has reached job max allowed time, kill job
 *  else, job has used up time slice but not yet used up all allowed time,
 *  send back to ready queue (memory)  with updated current time ( total time job has spent in memory )*/

    cout<< "TRo engaged"<<endl;
    long  timeElapsed = p[5] - (findRunningJob(runningJobNum))->getEnterTime();
    while ( p[1] != job -> getJobNum() ){ job++; } // makes jobtable iterator point to the job that triggered tro.

    if ( timeElapsed == job->getMaxTime()){
        // "kill job". Swap out not neccesary. Job table entry and memory space can be used by other job.
        cout << "TIMER RUNOUT" << endl << "TOTAL CPU TIME HAS EXCEEDED MAX TIME ALLOWED" << endl;
                terminateJob(findRunningJob(runningJobNum)->getJobNum());

    }
    else if (  timeElapsed < job->getMaxTime() ){
        cout << "TIMER RUNOUT" << endl << "TIME SLICE FINISHED, JOB SENT BACK TO MEMORY" << endl;
        //job->currTime =  job-> currTime + timeSlice ;  // total curr_time + Time Slice
    }
}


void swapper (long jnum){
  /* *Determines which jobs that are not in memory to swap into memory.
   *Call a routine that finds space in memory, then OS must call siodrum() to swap the job in.
   */
        long enoughSpace = 0;
        if ( !CurrentlySwapping ){
            while ( jnum != job-> getJobNum()){ job++; }
            //if ( !(job->getInMem())){
                enoughSpace = memory.findFreeSpace( job -> getJobSize() );
                /* If selected job fits in Memory,swap in to memory  */
                if ( enoughSpace != -1 ){
                    CurrentlySwapping = true;
                    job -> setJobStartLoc( enoughSpace );// findfreespace returns a base address for the job
                    job -> setJobEndLoc( enoughSpace + (job -> getJobSize())  );
                    //job -> setEnterTime(0);
                    siodrum( job -> getJobNum(), job-> getJobSize() , job->getJobStartLoc(), 0 );
                    memory.allocateMemory( job -> getJobNum(),job -> getJobStartLoc(), job->getJobEndLoc());
                    job -> setInMem (true);

                }
            }
}


void runJob(long &a, long p[]) {
	/*  Gets the next job to run from CPU Scheduler and runs that job. *
	*  CPU Scheduler should retunr a job number of a job that is in memory, and not blokcked*/

	long curr_job = CPU_scheduler();
    while (job->getJobNum() != curr_job) {  // look through the job table for the job number that CPU scheduler returned.
            job++;
    }

	if ( curr_job == -1 || job-> getBlocked() == true) {
            a = 1;
            cout<<  " im in run job. job is blocked"<<endl;
    }
    else{
        if ( !(job -> getInMem()) ){
            swapper(job -> getJobNum());
        }else{
            cout<< " Job is not blocked "<<endl<<"setting values for CPU to run"<<endl;
            a=2;
            job->setEnterTime(p[5]); // records the total CPU time of the job so far before it goes back to using the CPU

             // CPU in user mode
            p[2] = job->getJobStartLoc();
            p[3] = job->getJobSize() ;

            /*  checks to see if job can finish in less than a time slice, if not, job is given entire time slice,
            *  else job is given only enough time to finish
            */
            p[4] = timeSlice;

            job->setRunning(true);
        }
    }
}
void Dskint(long &a, long p[])
{
    while ( job -> getJobNum() != IOJobNum ){ job++; }

    cout << "DSKINT WORKING"<<endl;
    bookkeeper(p[5]);
    processingIO = false;
    job->setDoingIO(false);
    job -> setBlocked(false);
    job->setRunning(true);
    job->setRequestingIO(false);

    cout << "Position of IO Job" << IOJobNum << endl;


    if ( job -> getRunning() == false){
        terminateJob(job->getJobNum());
    }
    runJob(a, p);
}

void runIO()
{
       if ( (!processingIO) && (!IOQ.empty()) )
        {
            IOJobNum = IOQ.front();
            while (job->getJobNum() != IOJobNum){ job++; }             //Retrieve the first (oldest) element in the IO queue. make job point the the job

            if(job->getInMem())    //Check if the IOjob on the queue is in memory
            {
                cout<< " about to start doing i/o for job num: "<< job->getJobNum();
                siodisk(job->getJobNum());
                processingIO = true;
                IOQ.pop();                      //Removes the first (oldest) element in the IO queue
                job->setDoingIO(true);
            }
        }else cout<< "I/O already in progress or IOQ is empty"<<endl;
}

list<Job>::iterator findRunningJob(long jnum)
{
        for( job = JobTable.begin(); job != JobTable.end(); ++job )
        {
            if(job->getRunning())
                return job;
        }
}

list<Job>::iterator findIOJob(long jnum)
{
        for( job = JobTable.begin(); job != JobTable.end(); ++job )
        {
            if(job->getDoingIO())
                return job;
        }
}

list<Job>::iterator findInterruptedJob(long jnum)
{
        for( job = JobTable.begin(); job != JobTable.end(); ++job )
        {
            if(job->getJobNum() == jnum)
                return job;
        }
}


Job jobObj (long jnum) {
    for(job = JobTable.begin(); job != JobTable.end(); ++job)
    {
        if(job->getJobNum() == jnum)
            return *job;
    }
}
