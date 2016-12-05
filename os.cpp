#include <iostream>
#include <list>
#include <queue>
#include "job.h"
#include "memorymanager.h"

using namespace std;

static bool CurrentlySwapping;
static bool processingIO;
static MemoryManager memory;  // creates 100k of memory
static queue <Job> IOQ; // jobs waiting for I/O
static list <Job> JobTable; //should be intialized with space for 50 jobs
static list<Job>::iterator job = JobTable.begin();; // A global iterator for the job table. iterator points to the job object in the list.

void crint (int &a, int p[]) {		//A new job has arrived, information about the job is in array p.

	cout << "Crint Initiated." << endl;

	/* 
		p[1] = job number
	   	p[2] = priority
	  	p[3] = job size
	   	p[4] = max time
	   	p[5] = current time
	*/

	JobTable.push_back(new Job(p[1], p[2], p[3], p[4], p[5]));

	cout << "Crint completed." << endl;

	//TODO: Resume execution


	return;
}

void svc (int &a, int p[]) {

	cout << "SVC Initiated." << endl;

	/*
		If a = 5: the job is requesting termination.
		If a = 6: the job is requesting another disk I/O operation.
		If a = 7: the job requesting to be blocked until all pending I/O requests are completed.
	*/

	if(a[0] == 5) {

		cout << "SVC 5: Job requesting termination..." << endl;

		//Set killed bit of job to true if job is doing or requesting I/O
		if((*job)->doingIO == true || (*job)->requestingIO == true)
			(*job)->killed = true;

		//Finally, terminate the job
		terminatejob(job);

	}

	if(a[0] == 6) {

		cout << "SVC 6: Job requesting another I/O disk operation..." << endl;

		//Add the job number to the IO queue
		IOQ.push((*job)->job_num);

		//Set the requestingIO variable to true
		(*job)->requestingIO = true;

		//Check if it is the only job on the queue
		//Check if system is already doing I/O
		//If not, start IO on job requesting IO
		if(IOQ.size() == 1) && processingIO == false)
			startIO(job);		// TODO Tanzena: startIO function to be implemented

	}

	if(a[0] == 7) {

		cout << "SVC 7: Job requesting to be blocked until all pending I/O requests are completed..." << endl;

		//Set blocked bit of job to true if there are jobs using/waiting on the IO queue 
		if(!IOQ.empty() || processingIO == true)
			(*job)->blocked = true;
	}

	cout << "SVC completed." << endl;
	//TODO: Resume execution
	

	return;
}


void scheduler (int &a, int p[]) {

	cout << "CPU scheduler working" << endl;

	//TODO: Round robin

	return;
}

void bookkeeper(int currentTime) {

	cout << "Book keeper working" << endl;

	//TODO: Checks to see how much time a job has left to use the CPU


	return;
}


void terminateJob(list<Job>::iterator job) {
	//TODO Tanzena:Function to remove job from memory
	memory.removeJobFromMemory(job);

	//Change inMem variable of job to false
	(*job)->inMem = false;

	//Remove job from job table
	JobTable.erase(job);

	cout << "Job terminated." << endl;

	return;
}
