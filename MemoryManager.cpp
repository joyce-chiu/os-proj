//.cpp file code:

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <map>

using namespace std;

MemoryManager::MemoryManager()
{
	/* Initialize memory with 0's representing free space */
	
	memory = vector<int>(Collections::nCopies(MAX_SIZE, 0));
	fsTable = map<int, int>();
}

void MemoryManager::fillFreeSpaceTable()
{
	fsTable.clear(); // Clears the contents of the FST
	int FSbegin = -1;
	int FSend = -1;
	for (int i = 0; i < MAX_SIZE; i++)
	{
		if (memory[i] == 0)
		{
			FSbegin = i;
			FSend = i;
			for (int j = i; j < MAX_SIZE; j++)
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

int MemoryManager::findFreeSpace(int jobSize)
{
	for (auto entry : fsTable)
	{
		if (entry.second >= jobSize)
		{
			return entry.first;
		}
	}
	return -1;
}

int MemoryManager::allocateMemory(int jobSize)
{
	// Before allocating memory we call this function determine where there is free space
	fillFreeSpaceTable();
	int freeSpacePos = findFreeSpace(jobSize);
	if (freeSpacePos != -1)
	{
		for (int i = freeSpacePos; i < freeSpacePos + jobSize; i++)
		{
			memory[i] = 1;
		}
		return freeSpacePos;
	}
	return -1;
}

void MemoryManager::removeFromMemory(int addressInMemory, int jobSize)
{
	for (int i = addressInMemory; i < addressInMemory + jobSize; i++)
	{
		memory[i] = 0;
	}
}
			{
				startAddSet = false;
			}

		}
	}
	if (startAddSet)
	{
		for (int i = j->getAddress(); i < j->getAddress() + j->getJobSize(); i++)
		{
			memory[i] = 1;
		}
	j->setSwapping(true);
	return true;
	}
	return false;
}

void MemoryManager::removeFromMemory(Job *j)
{

	for (int i = j->Address(); i < j->Address() + j->JobSize(); i++)
	{
		memory[i] = 0;
	}
}

void MemoryManager::fillFreeSpaceTable()
{
	//fsTable.clear(); // Clears the contents of the FST
	int FSbegin = -1;
	int FSend = -1;
	for (int i = 0; i < MAX_SIZE; i++)
	{
		if (memory[i] == 0)
		{
			FSbegin = i;
			FSend = i;
			for (int j = i; j < MAX_SIZE; j++)
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

int MemoryManager::findFreeSpace(int jobSize)
{
	for (auto entry : fsTable)
	{
		if (entry.second >= jobSize)
		{
			return entry.first;
		}
	}
	return -1;
}

int MemoryManager::allocateMemory(int jobSize)
{
	// Before allocating memory we call this function determine where there is free space
	fillFreeSpaceTable();
	int freeSpacePos = findFreeSpace(jobSize);
	if (freeSpacePos != -1)
	{
		for (int i = freeSpacePos; i < freeSpacePos + jobSize; i++)
		{
			memory[i] = 1;
		}
		return freeSpacePos;
	}
	return -1;
}
