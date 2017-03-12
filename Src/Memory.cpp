#pragma once
#include "stdafx.h"
#include "Memory.h"
#include <iostream>

using namespace std;

Memory::Memory(int cap)
{
	capacity = cap;
	memory = new projWORD[capacity];
	clear();
}

Memory::Memory()
{
	capacity = 1024;
	memory = new projWORD[capacity];
	clear();
}

Memory::~Memory()
{
	delete[] memory;
}

void Memory::addWord(projWORD word)
{
	if (isFull())
		return;

	memory[size] = word;
	size++;
}

void Memory::setWord(int index, projWORD word)
{
	memory[index] = word; 
	//cout << "setting RAM at index: " << index << " to word: " << word << endl;
}

void Memory::clear()
{
	for (int i = 0; i < capacity; i++)
		memory[i] = 0;
	size = 0;
}
