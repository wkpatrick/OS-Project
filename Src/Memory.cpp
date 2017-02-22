#pragma once
#include "stdafx.h"
#include "Memory.h"

Memory::Memory(int cap)
{
	capacity = cap;
	memory = new WORD[capacity];
	for (int i = 0; i < capacity; i++)
		memory[i] = 0;
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
