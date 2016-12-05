#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H

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
private:
	const int MAX_SIZE = 100;
	std::vector<int> memory;

public:
	MemoryManager();

	virtual bool addToMemory(Job *j);

	virtual void removeFromMemory(Job *j);
};


#endif // MEMORYMANAGER_H
