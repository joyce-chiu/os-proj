#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H

#include <vector>
#include <map>

#include "JOB.H"

using namespace std;

class MemoryManager
{
public:

    const long  MAX_SIZE = 100;
    bool startAddSet;
	vector<long > memory;
	map<long , long > fsTable;

	MemoryManager();
	void removeFromMemory(long , long );
	void fillFreeSpaceTable();
	long  findFreeSpace(long  jobSize); //working
	void  allocateMemory(long jnum,long jobStart, long jobEnd); //working
};

#endif // MEMORYMANAGER_H
