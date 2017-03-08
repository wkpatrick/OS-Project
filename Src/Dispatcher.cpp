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

	cpuToSet->SetPCB(pcbs->getPCB(readyQ->front()));
	readyQ->pop();
}
