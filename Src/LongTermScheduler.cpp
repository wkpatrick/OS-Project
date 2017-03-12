#pragma once
#include "stdafx.h"
#include "LongTermScheduler.h"
#include <iostream>
#include <algorithm>
#include <list>
#include <chrono>

using namespace std;
using namespace std::chrono;

LongTermScheduler::LongTermScheduler(Memory *r, Memory *d, PCBList *_list, queue<int> *rQ, int schedulingMethod)
{
	disk = d;
	ram = r;
	pcbs = _list;
	readyQ = rQ;


	//FIFO
	switch (schedulingMethod)
	{
	case 0://FIFO
		for (int i = 1; i < 31; i++) {
			newQ.push(i);
			pcbs->getPCB(i)->pcbCount = i;
			pcbs->getPCB(i)->stats.loadTime = high_resolution_clock::now();
		}
			
		break;
	case 1://Priority
		priority_queue<int> pQ = priority_queue<int>();
		for (int i = 1; i < 31; i++)
			pQ.push(pcbs->getPCB(i)->priority);

		list<int> tempL;
		for (int i = 1; i < 31; i++)
			tempL.push_front(i);

		for (int i = 1; i < 31; i++) {
			for (int j = 1; j < 31; j++) {
				if (find(tempL.begin(), tempL.end(), j) != tempL.end()) {
					if (pcbs->getPCB(j)->priority == pQ.top()) {
						pcbs->getPCB(j)->pcbCount = j;
						pcbs->getPCB(j)->stats.loadTime = high_resolution_clock::now();
						newQ.push(j);
						tempL.remove(j);
						pQ.pop();
					}
				}
			}
		}
		break;
	}

	
}

LongTermScheduler::~LongTermScheduler()
{
}


void LongTermScheduler::LoadProcessesToRam()
{	
	if (readyQ->size() >= 10 || newQ.size() == 0)
		return;

	if (readyQ->size() == 0) {
		ram->clear();
		while (readyQ->size() < 10) {
			PCB *process = pcbs->getPCB(newQ.front());

			int spaceNeeded = process->codeSize + process->inputBufferSize + process->outputBufferSize
				+ process->tempBufferSize;

			//add process data to ram if space is avaliable
			if (ram->getAvaliableSpace() >= spaceNeeded) {
				process->codeStartRamAddress = ram->getSize();
				process->pc = ram->getSize();
				for (unsigned int i = 0; i < process->codeSize; i++)
					ram->addWord(disk->getWord(process->codeStartDiskAddress + i));				

				process->inputBufferRamAddress = ram->getSize();
				for (int i = 0; i < process->inputBufferSize; i++)
					ram->addWord(disk->getWord(process->dataStartDiskAddress + i));

				process->outputBufferRamAddress = ram->getSize();
				for (int i = 0; i < process->inputBufferSize; i++)
					ram->addWord(0x0);

				process->tempBufferRamAddress = ram->getSize();
				for (int i = 0; i < process->inputBufferSize; i++)
					ram->addWord(0x0);

				//add process to read queue and remove from new queue
				readyQ->push(newQ.front());
				newQ.pop();
				//add space stat
				process->stats.ramSpaceUsed = (float)spaceNeeded / 1024;
				
				//cout << hex << ram->getWord(PCBlist->getPCB(3)->codeStartRamAddress) << endl;
			}
		}
	}

	
}
