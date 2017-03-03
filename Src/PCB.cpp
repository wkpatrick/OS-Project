#pragma once
#include "stdafx.h"
#include "PCB.h"

PCBList::PCBList()
{
	for (int i = 1; i < numJobs; i++)
		pcbs[i] = new PCB();
}

PCBList::~PCBList()
{
	for (int i = 1; i < numJobs; i++)
		delete pcbs[i];
}

