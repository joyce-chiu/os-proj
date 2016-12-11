#include <iostream>
using namespace std;
#include "job.h"   // include the job class
#include "memorymanager.h" // inludes the memory manager class
#include <list>
#include<queue>


static bool CurrentlySwapping;
static bool processingIO;
static MemoryManager memory;  // creates 100k of memory
static queue <Job> IOQ; // jobs waiting for I/O
static list <Job> JobTable; //should be intialized with space for 50 jobs
static list<Job>::iterator job = JobTable.begin(); // A gloabl joberator for the job table. iterator points to the job object in the list.
static const int timeSlice = 5;

void startup (){

    sos.ontrace();
    CurrentlySwapping = false;
    processingIO = false;
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

    while ( p[1] != job -> number ){ job++; } // makes jobtable iterator point to the job that triggered tro.

    if ( job-> currTime >=  job->maxTime){
        // "kill job". Swap out not neccesary. Job table entry and memory space can be used by other job.
        cout << "TIMER RUNOUT" << endl << "TOTAL CPU TIME HAS EXCEEDED MAX TIME ALLOWED" << endl;
		JobTable.erase(*job);
	    	removeFromMemory(*job);
	    	
        // call function to delete job from memory
    }
    else if (  job->currTime <   job->maxTime ){
        cout << "TIMER RUNOUT" << endl << "TIME SLICE EXCEEDED, JOB SENT BACK TO MEMORY" << endl;

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
		while ( Job != JobTable.end() ){ 
			if  ( !(job -> inMem) ){
				/* If selected job fits in Memory,swap in to memory  */
				enoughSpace = findFreeSpace ( job -> size );
			if ( enoughSpace != -1 ){
				CurrentlySwapping = true;
				sos.siodrum( job -> job_num, job -> size, job -> address, 0 );
				memory.addToMemorry( *job );
				job -> inMem = true;
				cout << " Swap succesfull "<< end;
			}else job++; // if does not fit in memory increment iterator to the next job
			}else job++; // if job already in memory, increment iterator to the next job
		}	
	}
}
	

void runJob(){
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
            p[4] = (job -> size > timeSlice) ? timeSlice :  job -> size;
	    job ->running = true;
     } else a = 1; // CPU set to idle

}
