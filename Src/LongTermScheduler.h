#pragma once
#include "Memory.h"
#include "PCB.h"
#include <queue>

using namespace std;

class LongTermScheduler
{
public:
	//scheduling method id: 0 = FIFO, 2 = Priority, 3 = SJF
	LongTermScheduler(Memory *r, Memory *d, PCBList *list, queue<int> *rQ, int schedulingMethod);
	~LongTermScheduler();
	//loads processes from disk into ram until ready queue is full
	//and only fills it up when the ready queue is empty
	void LoadProcessesToRam();

	//returns true if all jobs have been loaded and executed
	bool AllJobsFinished() { return (newQ.size() == 0) && (readyQ->size() == 0); }

private:
	Memory *disk, *ram;
	PCBList* pcbs;
	queue<int> *readyQ;
	queue<int> newQ;
};

