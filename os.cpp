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
static int curr_job; //the job number of the current running job.


void crint (int &a, int p[]) {		//A new job has arrived, information about the job is in array p.

	cout << "Crint Initiated." << endl;

	bookkeeper(p[5]);

	/* 
		p[1] = job number
	   	p[2] = priority
	  	p[3] = job size
	   	p[4] = max time
	   	p[5] = current time
	*/

	if(JobTable.size() < 50) {
		JobTable.push_back(new Job(p[1], p[2], p[3], p[4], p[5]));
		
		cout << "Crint completed." << endl;
	}
	else cout << "JobTable is full." << endl;

	runJob();
	return;
}

void svc (int &a, int p[]) {

	cout << "SVC Initiated." << endl;

	bookkeeper(p[5]);

	/*
		If a = 5: the job is requesting termination.
		If a = 6: the job is requesting another disk I/O operation.
		If a = 7: the job requesting to be blocked until all pending I/O requests are completed.
	*/

	if(a[0] == 5) {

		cout << "SVC 5: Job requesting termination..." << endl;

		//Set killed bit of job to true if job is not doing I/O
		if(job->doingIO == false)
			job->killed = true;
		
		//Finally, terminate the job if kill bit is true
		if(job->killed == true)
			terminatejob(job);

	}

	if(a[0] == 6) {

		cout << "SVC 6: Job requesting another I/O disk operation..." << endl;

		//Set the requestingIO variable to true
		job->requestingIO = true;

		//Add the job number to the IO queue
		IOQ.push(job->job_num);

		//Check if it is the only job on the queue
		//Check if system is already doing I/O
		//If not, start IO on job requesting IO
		if(IOQ.size() == 1) && processingIO == false)
			siodisk(job->job_num);

	}

	if(a[0] == 7) {

		cout << "SVC 7: Job requesting to be blocked until all of its pending I/O requests are completed..." << endl;

		//Set blocked bit of job to true if job is requesting for I/O
		if(job->requestingIO == true)
			job->blocked = true;
		else job->blocked = false;
	}

	cout << "SVC completed." << endl;
	runJob();
	return;
}


int CPU_scheduler (int &a, int p[]) {

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


void terminateJob()

	//TODO Tanzena:Function to remove job from memory
	memory.removeJobFromMemory(job);

	//Change inMem variable of job to false
	job->inMem = false;

	//Remove job from job table
	JobTable.erase(job);

	cout << "Job terminated." << endl;

	return;
}
