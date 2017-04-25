#pragma once
#include "Page.h"
#include "Memory.h"
#include "PCB.h"
#include <deque>

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
	void setWord(int index, WORD set);
	bool isInLastUsed(int pageNum);

	deque<int> lastUsed;
	int numOfPages;
	Page* pages; //The array of pages, set to be a pointer cause you cant make an empty array;
	PCB *pcb;



};

