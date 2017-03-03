#pragma once
#include "stdafx.h"
#include "LongTermScheduler.h"
#include <iostream>

using namespace std;

LongTermScheduler::LongTermScheduler(Memory *r, Memory *d, PCBList *list, queue<int> *rQ)
{
	disk = d;
	ram = r;
	PCBlist = list;
	readyQ = rQ;

	//FIFO
	for (int i = 1; i < 31; i++)
		newQ.push(i);
	
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
			PCB *process = PCBlist->getPCB(newQ.front());

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
				
				//cout << hex << ram->getWord(PCBlist->getPCB(3)->codeStartRamAddress) << endl;
			}
		}
	}

	
}
