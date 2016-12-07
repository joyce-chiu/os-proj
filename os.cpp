#include < iostream>
using namespace std;
#include "job.h"   // include the job class
#include "MemoryManager.h" // inludes the memory manager class


	static MemoryManager memory;  // creates 100k of memory
	static queue <job> IOQ; // jobs waiting for IO
	static bool CurrentlySwapping;
	static bool processingIO;

void startup (){ // Declares all variables

	sos.ontrace();
	static job JobTable [][]; // stores jobs that are not in the system but not in memory Perhaps a linked list would work better.
	memory = new MemoryManager();
	IOQ = new queue <job>
	CurrentlySwapping = false;
	ProcessingIO = false; 
}


void Dskint(int &a, int p[])
{
		cout << string("DSKINT WORKING") << endl;
	
		bookkeeper(p[5]);
		//notify that I/O was completed
		//function should find job that was send to do I/O
		//mark that I/O for that job was done and 
		//select new job from IO queue to do I/O and send it to do I/O
		processingIO = false;
		int posOfIOJob = findJobDoingIO();
		cout << posOfIOJob << endl;
		jobTable->get(posOfIOJob).setDoingIO(false);
		jobTable->get(posOfIOJob).setBlocked(false);
		jobTable->get(posOfIOJob).setRequestIO(false);
		if (jobTable->get(posOfIOJob).getKilled())
		{
			terminateJob(posOfIOJob);
		}
		runIO();
		runJob(a,p);
}


void drmint ( int &a, int p [] ){

}


void tro ( int &a, int p [] ){

	

}
