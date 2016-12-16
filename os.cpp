#include <iostream>
using namespace std;
#include "job.h"   // include the job class
#include "memorymanager.h" // inludes the memory manager class
#include <list>
#include<queue>

static bool CurrentlySwapping;
static bool processingIO;



static queue <int> IOQ; // jobs waiting for I/O

static list <Job> JobTable; //should be intialized with space for 50 jobs
static list<Job>::iterator job = JobTable.begin(); // A gloabl joberator for the job table. iterator points to the job object in the list.

static const int timeSlice = 5000; //in miliseconds

static MemoryManager memory;  // creates 100k of memory

void startup (){
    sos.ontrace();
    CurrentlySwapping = false;
    processingIO = false;
}

void crint (int &a, int p[]) {		//A new job has arrived, information about the job is in array p.

        cout << "Crint Initiated." << endl;

        bookkeeper(p[5]);

        /* 	p[1] = job number
                p[2] = priority
                p[3] = job size
                p[4] = max time
                p[5] = current time
        */

        if(JobTable.size() < 50) {
                JobTable.push_back(Job(p[1], p[2], p[3], p[4], p[5] ) );// removed "new keyword. It wa giving compilation error"
                cout << "Crint completed." << endl;
        }
        else cout << "JobTable is full." << endl;

        runJob(a,p);
        return;
}

void svc (int &a, int p[]) {

        cout << "SVC Initiated." << endl;

        bookkeeper(p[5]);

        /*	If a = 5: the job is requesting termination.
                If a = 6: the job is requesting another disk I/O operation.
                If a = 7: the job requesting to be blocked until all pending I/O requests are completed.
        */

        if(a == 5) {    // a is not an array but a regualr int.

                cout << "SVC 5: Job requesting termination..." << endl;

                //Set killed bit of job to true if job is not doing I/O
                if(job->doingIO == false)
                        job->killed = true;

                //Finally, terminate the job if kill bit is true
                if(job->killed == true)
                        terminatejob(job -> job_num);

        }

        if(a == 6) {    // a is not an array but a regualr int.

                cout << "SVC 6: Job requesting another I/O disk operation..." << endl;

                //Set the requestingIO variable to true
                job->requestingIO = true;

                //Add the job number to the IO queue
                IOQ.push(job->job_num); // queue is a LIFO stucture. be default push(),adds to the end of the queue

                //Check if it is the only job on the queue
                //Check if system is already doing I/O
                //If not, start IO on job requesting IO
                if( (IOQ.size() == 1) && (processingIO == false)){
                        siodisk(job->job_num);
                }

        }

        if(a == 7) {    // a is not an array but a regualr int.

                cout << "SVC 7: Job requesting to be blocked until all of its pending I/O requests are completed..." << endl;

                //Set blocked bit of job to true if job is requesting for I/O
                if(job->requestingIO == true)
                        job->blocked = true;
                else job->blocked = false;
        }

        cout << "SVC completed." << endl;
        runJob(a,p);
        return;
}


int CPU_scheduler () {

        //Select the next job to use the CPU and return the job number
        //The job is selected only if it is not blocked
        //If there are no more jobs on the job table, return -1

        cout << "CPU scheduler working" << endl;

        int scheduledJob;	// Integer variable to hold the job number to use the CPU

        while(!JobTable.empty()) {
                if(job->blocked == false) {
                        scheduledJob = job->job_num;
                        return scheduledJob;
                }
                job++;
        }
        return -1;
}

void bookkeeper(int currentTime) {

        //This function calculates how much time the job spent on the CPU before it was interrupted and saves the new maxTime of the job

        cout << "Book keeper working" << endl;

        int timeElapsed = currentTime - job->enterTime;
        int timeRemain = job->maxTime - timeElapsed;

        job->maxTime = timeRemain;

        return;
}


void terminateJob(int jnum){


        //TODO Tanzena:Function to remove job from memory
        while ( jnum != job -> job_num ){ job++; }

        memory.removeFromMemory(job-> address, job ->size);

        //Change inMem variable of job to false
        job ->inMem = false;

        //Remove job from job table
        JobTable.erase(job);

        cout << "Job terminated." << endl;

        return;
}


void drmint ( int &a, int p [] ){
     cout << "DRUM INTERRUPT" << endl << "Swap has finished. Setting flags." << endl;
        /*  Drum has finished swapping a job into of memory.  */

    /*  update swapped job in the job table
       Loop through job table looking for the job that was set to swap and reset flags
      */
    CurrentlySwapping = false;
    for( job = JobTable.begin(); job != JobTable.end(); ++job ){
           if (  job->swapping ) {
                job->swapping = false;
                job->inMem = true;
                break; // Once job info is updated, stop iterating through list.
           }
    }
}



// I THINK THE LOGIC FOR THE TRO FUNCTION WORKS. I DONT KNOW IF THE CODE WORKS!
void tro ( int &a, int p [] ){

/*  if  a job has reached job max allowed time, kill job
 *  else, job has used up time slice but not yet used up all allowed time,
 *  send back to ready queue (memory)  with updated current time ( total time job has spent in memory )*/

    int timeElapsed = job -> currTime - job ->enterTime;
    while ( p[1] != job -> job_num ){ job++; } // makes jobtable iterator point to the job that triggered tro.

    if ( timeElapsed = job->maxTime){
        // "kill job". Swap out not neccesary. Job table entry and memory space can be used by other job.
        cout << "TIMER RUNOUT" << endl << "TOTAL CPU TIME HAS EXCEEDED MAX TIME ALLOWED" << endl;
                terminateJob(job -> job_num);

    }
    else if (  timeElapsed < job->maxTime ){
        cout << "TIMER RUNOUT" << endl << "TIME SLICE FINISHED, JOB SENT BACK TO MEMORY" << endl;
        job->currTime =  job-> currTime + timeSlice ;  // total curr_time + Time Slice
    }
}



void swapper (){
  /* *Determines which jobs that are not in memory to swap into memory.
   *Call a routine that finds space in memory, then OS must call siodrum() to swap the job in.
   */
        int enoughSpace = 0;
        if ( !CurrentlySwapping ){
                //Search through the job table for a job noT in Memory
                job = JobTable.begin();
                while ( job != JobTable.end() ){
                        if  ( !(job -> inMem) ){
                            enoughSpace = memory.findFreeSpace( job -> size );
                            /* If selected job fits in Memory,swap in to memory  */
                            if ( enoughSpace != -1 ){
                                    CurrentlySwapping = true;
                                    sos.siodrum( job -> job_num, job -> size, job -> address, 0 );
                                    memory.allocateMemory(job ->size);
                                    job -> inMem = true;
                                    cout << " Swap succesfull "<< endl;
                            }
                        }
                        job++; // if job already in memory, or too big for current memory space, increment iterator to the next job
                }
        }
}


void runJob(int &a, int p[]){
    /*  Gets the next job to run from CPU Scheduler and runs that job. *
     *  CPU Scheduler should retunr a job number of a job that is in memory, and not blokcked*/
    int curr_job = CPU_scheduler();

    if ( curr_job != -1 ){ 	// if CPU Scheduler returns -1, there are no jobs in the job  table
            while ( job -> job_num != curr_job ){  // look through the job table for the job number that CPU scheduler returned.
                job++;
            }

            job -> enterTime = job -> currTime; // records the total CPU time of the job so far before it goes back to using the CPU

            a = 2; // CPU in user mode
            p[2] = job ->address;
            p[3] = job ->size;

            /*  checks to see if job can finish in less than a time slice, if not, job is given entire time slice,
             *  else job is given only enough time to finish
            */
            p[4] = (job -> maxTime > timeSlice) ? timeSlice :  job -> maxTime;
            job ->running = true;
     } else a = 1; // CPU set to idle
}



void Dskint(int &a, int p[])
{
                cout << "DSKINT WORKING" << endl;
                bookkeeper(p[5]);
                job -> doingIO = false;
                int posOfJob = findIOJob();
                cout << "Position of IO Job: " << posOfJob << endl;
                job->doingIO = false;
                job->running = true;
                job->requestingIO = false;
                if ( job -> running == false)
                {
                    terminateJob(findJobTablePos( IOJob->jobnum));
                }
                runIO();
                runJob(a, p);
}

void runIO()
{
        if ( (!processingIO) && (!IOQ.empty()) )
        { 
            for ( job : IOQ)
            {
                if (job->inMem)
                {
                        sos::siodisk(job->job_num);
                        IOQ->remove(job);
                        JobTable(findJobTablePos(job->job_num))->doingIO = true;
                        JobTable(findJobTablePos(job->job_num))->requestingIO = true;
                        doingIO = true;
                        break;
                }
            }

        }
}

int findRunningJob()
{
        int jobtablePos = -1;
        for (int i = 0; i < JobTable.size(); i++)
        {
                if (job -> running)
                {
                        jobtablePos = i;
                }
        }
        return jobtablePos;
}

int findIOJob()
{
        int jobtablePos = -1;
        for (int i = 0; i < JobTable.size(); i++)
        {
                if ( job -> doingIO )
                {
                        jobtablePos = i;
                }
        }
        return jobtablePos;
       
    /*while ( job -> doingIO == false ){ job++; }
    return job -> job_num;
    */
}

int findJobTablePos(int job_num)
{
        for (int i = 0; i < JobTable.size(); i++)
        {
                if ( job ->job_num == job_num)
                {
                        return i;
                }
        }
        return -1;
}

