#pragma once
#include "stdafx.h"
#include "Memory.h"

Memory::Memory(int cap)
{
	capacity = cap;
	memory = new WORD[capacity];
	clear();
}

Memory::Memory()
{
	capacity = 1024;
	memory = new WORD[capacity];
	clear();
}

Memory::~Memory()
{
	delete[] memory;
}

void Memory::addWord(WORD word)
{
	if (isFull())
		return;

	memory[size] = word;
	size++;
}

void Memory::clear()
{
	for (int i = 0; i < capacity; i++)
		memory[i] = 0;
	size = 0;
}
