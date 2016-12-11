#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H

class MemoryManager
{
public:
	static constexpr int MAX_SIZE = 100;
private:
	std::vector<int> memory;
	std::map<int, int> fsTable;

	/// <summary>
	/// memorymanager()
	/// Initialize memory with 0's representing free space
	/// </summary>
public:
	MemoryManager();

	/// <summary>
	/// fillFreeSpaceTable()
	/// Locates where in memory there is free space and puts the free space size
	/// as the key and the address of the free space as the value.
	/// </summary>
private:
	void fillFreeSpaceTable();

	/// <summary>
	/// findFreeSpace()
	/// Determines if there is enough space for the current job size
	/// If so, return the starting address else return -1 (not enough space)
	/// </summary>
public:
	virtual int findFreeSpace(int jobSize);

	/// <summary>
	/// Process of allocating memory for the current jobSize
	/// </summary>
	virtual int allocateMemory(int jobSize);

	/// <summary>
	/// If a job is terminated then this function is called to reset the memory
	/// so it can be used by other jobs
	/// </summary>
	virtual void removeFromMemory(int addressInMemory, int jobSize);
};
