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
		bookKeep(p[5]);
		doingIO = false;
		int posOfJob = findIOJob();
		cout << "Position of IO Job: " << posOfJob << endl;
		job->doingIO = false;
		job->running = true;
		job->requestingIO = false;
		if (Job->running = false)
		{
			terminateJob(findJobTablePos(IOJob->jobnum));
		}
		runIO();
		runJob(a, p);
}

void runIO()
{
	if (!doingIO)
	{
		if (!IOQ->isEmpty())
		{
			for (job : IOQ)
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
}

int findRunningJob()
{
	int jobtablePos = -1;
	for (int i = 0; i < JobTable->size(); i++)
	{
		if (JobTable(i).running)
		{
			jobtablePos = i;
		}
	}
	return jobtablePos;
}

int findIOJob()
{
	int jobtablePos = -1;
	for (int i = 0; i < JobTable->size(); i++)
	{
		if (JobTable(i).doingIO)
		{
			jobtablePos = i;
		}
	}
	return jobtablePos;
}

int findJobTablePos(int job_num)
{
	for (int i = 0; i < JobTable->size(); i++)
	{
		if (JobTable(i)->job_num == job_num)
		{
			return i;
		}
	}
	return -1;
}



void drmint ( int &a, int p [] ){

}


void tro ( int &a, int p [] ){

	

}
