#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <map>

#include "MEMORYMANAGER.H"

using namespace std;

MemoryManager::MemoryManager()
{
	/* Initialize memory with 0's representing free space */

	memory = vector<long>(MAX_SIZE, 0);
	fsTable = map<long, long>(); // each map entry takes in a jobs start and end location in mem

}

void MemoryManager::fillFreeSpaceTable()
{
	fsTable.clear(); // Clears the contents of the FST
	long  FSbegin = -1;
	long  FSend = -1;
	for (long  i = 0; i < MAX_SIZE; i++)
	{
		if (memory[i] == 0)
		{
			FSbegin = i;
			FSend = i;
			for (long  j = i; j < MAX_SIZE; j++)
			{
				if (memory[j] == 0)
				{
					FSend = j;
				}
				else if (memory[j] == 1)
				{ //End of free space
					break; //Break out because it found the end of free space
				}
			}
			i = FSend; //To move i to the end of free space so it can look for the next one
		}
		if (FSbegin != -1 && FSend != -1)
		{
			fsTable[FSbegin] = FSend - FSbegin + 1;
		}
	}
}

long  MemoryManager::findFreeSpace(long  jobSize)
{
    if ( fsTable.empty() ){
        return 0;
    }
    else {
        long lastMemVal = fsTable.rbegin()->first;// last entry in the table
        if( MAX_SIZE >= lastMemVal + jobSize ){ // fsTable.rbegin maps to the last occupied memory cell.
            long nextFreespace = lastMemVal + 1;

            cout<< "You Fit at Mem[" << nextFreespace<<"]"<<endl;

            return nextFreespace;
        }
        else return -1;
    }
}

void  MemoryManager::allocateMemory(long jnum, long jobStart, long jobEnd)
{
	// Before allocating memory we call this function determine where there is free space
	//fillFreeSpaceTable();
	//long freeSpacePos = findFreeSpace(j.getJobSize());
		for (long i = jobStart; i < jobEnd ; i++)
		{
			memory[i] = 1;
		}
		//return freeSpacePos;
}

void MemoryManager::removeFromMemory(long  startPos, long  endPos)
{

	for (long  i = startPos; i <= endPos; i++)
	{
		memory[i] = 0;
	}
}
