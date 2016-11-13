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


void drmint ( int &a, int p [] ){

}


void tro ( int &a, int p [] ){

	

}
