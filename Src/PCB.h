#pragma once
#include <chrono>

using namespace std::chrono;

enum STATUS
{
	RUNNING,
	READY,
	WAIT,
	NEW,
	TERMINATED
};

struct PerformanceStats {
	high_resolution_clock::time_point loadTime, beginTime, waitTime, completionTime;
	int ioReadCount, ioWriteCount = 0;
	int cacheWriteCount = 0;
	int pageFaults = 0;
	float ramSpaceUsed, cacheSpaceUsed;
};

struct PCB {
	unsigned int cpuID;
	unsigned int pc;	//program counter
	unsigned int pcbCount;
	int status;	//STATUS enum used for this
	unsigned int codeSize;
	int priority;	// high # = high priority
	int registers[16];
	PerformanceStats stats;
	int inputBufferSize;
	int outputBufferSize;
	int tempBufferSize;
	//addresses are start index of disk/ram array
	//EX: if input buffer if from indices 134 - 150, inputBufferRamAddress would equal 134
	unsigned int inputBufferRamAddress;
	unsigned int outputBufferRamAddress;
	unsigned int tempBufferRamAddress; 
	unsigned int codeStartDiskAddress;
	unsigned int codeStartRamAddress;
	unsigned int dataStartDiskAddress;
};

class PCBList
{
public:
	PCBList();
	~PCBList();

	//insert new pcb at location jobID
	//make sure inserted PCB was made in the heap
	//void insert(int jobID, PCB pcb) { pcbs[jobID] = pcb; }
	//returns a pointer of the PCB with jobID
	PCB* getPCB(int jobID) { return pcbs[jobID]; }

private:
	static const int numJobs = 31;
	//the index of the pcb is the jobs ID
	//0 is not used since first jobID is 1
	PCB *pcbs[numJobs];
};

