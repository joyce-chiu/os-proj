#include <iostream>
using namespace std;
#include "job.h"   // include the job class
#include "memorymanager.h" // inludes the memory manager class
#include <list>
#include<queue>


static bool CurrentlySwapping;
static bool processingIO;
static MemoryManager memory;  // creates 100k of memory
static queue <job> IOQ; // jobs waiting for I/O
static list <job> JobTable(); //should be intialized with space for 50 jobs
static JobTable::iterator job; // A gloabl joberator for the job table. iterator points to the job object in the list.


void startup (){

    sos.ontrace();
    CurrentlySwapping = false;
    processingIO = false;
}


void drmint ( int &a, int p [] ){
	cout << "DRUM INTERRUPT" << endl << "Swap has finished. Setting flags." << endl;
	/* Drum has finished swapping a job in/out of memory. */

    /* move swapped job out of the job table
     * Loop through job table looking for the job that was set to swap and set flags.
     */
    for( job = JobTable.begin(); job != JobTable.end(); ++job ){
           if ( *job.swapping ) {
               *job.swapping = false;
               *job.inMem = true;
               break; // Once job info is updated, stop iterating through list.
           }
    }

}

// I THINK THE LOGIC FOR THE TRO FUNCTION WORKS. I DONT KNOW IF THE CODE WORKS!

void tro ( int &a, int p [] ){
	
/* if  a job has reached job max allowed time, kill job
 * else if job has used up time slice but not yet used up all allowed time,
 * send back to ready queue (memory)*/

    if ( *job.curr_time >= *job.MaxTime	){    
        // "kill job". Swap out not neccesary. Job table entry and memory space can be used by other job.
        cout << "TIMER RUNOUT" << endl << "TOTAL CPU TIME HAS EXCEEDED MAX TIME ALLOWED" << endl;
		JobTable.erase( job );
    }
    else if ( *job.curr_time <  *job.Maxtime ){
        cout << "TIMER RUNOUT" << endl << "TIME SLICE EXCEEDED, JOB SENT BACK TO MEMORY" << endl;

        *job.curr_time = *job.curr_time + /* time slice  */ ;  // total curr_time + Time Slice
    }
}

void swapper (){
/* Determines which jobs that are not in memory to swap into memory.
 *
 * Call a routine that finds space in memory, then OS must call siodrum() to swap the job in.
 */
	if ( !CurrentlySwapping ){	
		job = JobTable.begin();
		while ( job != JobTable.end()){
			if ( !(*job.inMem ) && /* job fits in memory */) {
					CurrentlySwapping = true;
					sos.siodrum(*job.job_num, *job.size, *job.address, 0);
			}
				else job++; // if job too big for current memory space or already in memory, move to next job in table.
				
		}
	}
}
	

