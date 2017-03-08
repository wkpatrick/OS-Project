#pragma once
#include <queue>
#include "cpu.h"
#include "PCB.h"

using namespace std;

class Dispatcher
{
public:
	Dispatcher(queue<int> *rQ, PCBList *pcbL);
	~Dispatcher();
	void Dispatch(CPU *cpuToSet);
private:
	queue<int> *readyQ;
	PCBList *pcbs;
};

