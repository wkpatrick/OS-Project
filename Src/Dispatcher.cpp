#pragma once
#include "stdafx.h"
#include "Dispatcher.h"

Dispatcher::Dispatcher(queue<int> *rQ, PCBList *pcbL)
{
	readyQ = rQ;
	pcbs = pcbL;
}

Dispatcher::~Dispatcher()
{
}

void Dispatcher::Dispatch(CPU *cpuToSet)
{
	if (readyQ->empty())
		return;

	//Have it pull off the waiting queue before readyQ?
	cpuToSet->SetPCB(pcbs->getPCB(readyQ->front()));
	readyQ->pop();
}
