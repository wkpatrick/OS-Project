#pragma once
#include "Page.h"
#include "Memory.h"
#include "PCB.h"
#include <deque>
#include <vector>

typedef unsigned long int WORD;
using namespace std;

class PageTable
{
public:
	PageTable(PCB *pcb);
	PageTable();
	~PageTable();

	void loadIntoFrames(Memory mem);
	void reorderLastUsed(int pageNum);
	WORD getWord(int index);
	WORD getNoPageWord(int index);
	void setWord(int index, WORD set);
	bool isInLastUsed(int pageNum);

	deque<int> lastUsed;
	int numOfPages;
	vector<Page> pages;
	PCB *pcb;



};

