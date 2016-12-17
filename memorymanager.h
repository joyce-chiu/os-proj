#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H

#include "JOB.H"
#include <vector>

using namespace std;

//.h file code:

/// <summary>
/// * Should be able to add to the memory
/// delete from the memory
/// find free space for job
/// </summary>
//package osProject;


///
/// <summary>
/// @author Tanzena
/// </summary>
//TODO Tanzena
class MemoryManager
{
public:

    const int MAX_SIZE = 100;
	vector<int> memory;
	map<int, int> fsTable;

	MemoryManager();

	virtual bool addToMemory(Job *j);
	virtual void removeFromMemory(Job *j);
	void fillFreeSpaceTable();
	int findFreeSpace(int jobSize);
	int allocateMemory(int jobSize);
};


#endif // MEMORYMANAGER_H
