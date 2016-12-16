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
#ifndef MEMORYMANAGER_H

#include <vector>
#include <map>

class MemoryManager
{
public:
        static constexpr int MAX_SIZE = 100;
        virtual int findFreeSpace(int jobSize); // Determines if there is enough space for the current job size
                                                // If so, return the starting address else return -1 (not enough space)
        virtual int allocateMemory(int jobSize); // Process of allocating memory for the current jobSize
        virtual void removeFromMemory(int addressInMemory, int jobSize); // If a job is terminated then this function is called to reset the memory
                                                                        // so it can be used by other jobs
        MemoryManager(); // Initialize memory with 0's representing free space
private:
        vector<int> memory;
        map<int, int> fsTable;
        void fillFreeSpaceTable(); // Locates where in memory there is free space and puts the free space size
                                  // as the key and the address of the free space as the value.
};

#endif // MEMORYMANAGER_H

