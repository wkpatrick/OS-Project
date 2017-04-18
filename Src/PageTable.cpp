#include "stdafx.h"
#include "PageTable.h"
#include <iostream>

using namespace std;

PageTable::PageTable(PCB *pcb)
{
	this->pcb = pcb;
}

PageTable::PageTable()
{

}


PageTable::~PageTable()
{
}

void PageTable::loadIntoFrames(Memory mem)
{
	this->numOfPages = mem.getCapacity() / 4;
	this->pages = new Page[numOfPages];

	int addr = 0;
	for (int i = 0; i < numOfPages; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			pages[i].contents[j] = mem.getWord((i * 4) + j);
		}
	}
}

void PageTable::reorderLastUsed(int pageNum)
{
	deque<int> copy;

	while (this->lastUsed.front() != pageNum)
	{
		copy.push_front(this->lastUsed.front());
		this->lastUsed.pop_front();
	}

	copy.push_back(pageNum);
	this->lastUsed.pop_front();


	for (int i = 0; i < copy.size(); i++)
	{
		this->lastUsed.push_front(copy.front());
		copy.pop_front();
	}
}

WORD PageTable::getWord(int index)
{
	int reqPageNum = index / 4;
	int reqLine = index % 4;

	if (this->lastUsed.size() == 0)
	{
		this->lastUsed.push_front(reqPageNum);
		return this->pages[reqPageNum].contents[reqLine];
	}

	else if (isInLastUsed(reqPageNum))
	{
		this->reorderLastUsed(reqPageNum);
		return this->pages[reqPageNum].contents[reqLine];
	}
	
	else
	{
		this->pcb->stats.pageFaults++;

		this->lastUsed.push_front(reqPageNum);
		this->lastUsed.resize(4);
		return this->pages[reqPageNum].contents[reqLine];
	}
}

bool PageTable::isInLastUsed(int pageNum)
{
	if (this->lastUsed.size() == 0)
	{
		return false;
	}
	for (int i = 0; i < lastUsed.size(); i++)
	{
		if (this->lastUsed.at(i) == pageNum)
		{
			return true;
		}
	}
	return false;
}
