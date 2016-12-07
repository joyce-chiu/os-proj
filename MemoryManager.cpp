//.cpp file code:

#include <string>
#include <vector>
#include <list>
#include <iostream>

MemoryManager::MemoryManager()
{
	memory = std::list<>();
	for (int i = 0; i < MAX_SIZE; i++)
	{
		memory.push_back(0);
	}
}

bool MemoryManager::addToMemory(Job *j)
{
	std::wcout << std::wstring(L"addToMemory WORKING") << std::endl;

	int sizeNeeded = j->getJobSize();
	bool startAddSet = false;
	int startAdd = -1;
	int endAdd;
	//int space = 0;
	for (int i = 0; i < MAX_SIZE; i++)
	{ //find spase in memory for job
		if (memory[i] == 0 && startAddSet == false)
		{
			startAdd = i;

			startAddSet = true;
		}


		if ((memory[i] == 1 && startAddSet) || i == 99)
		{

			endAdd = i;
			if ((endAdd - startAdd) >= sizeNeeded)
			{ //check if right size for our job
				j->setAddress(startAdd); //assign starting address for tis job
				//j.setInMemory(true);
				break;
			}
			else
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

	for (int i = j->getAddress(); i < j->getAddress() + j->getJobSize(); i++)
	{
		memory[i] = 0;
	}
}
