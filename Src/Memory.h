#pragma once
typedef unsigned long int WORD;

class Memory
{
public:
	Memory(int size);
	Memory();
	~Memory();
	//add a word at the next avaliable location
	void addWord(WORD word);
	void setWord(int index, WORD word) { memory[index] = word; }
	WORD getWord(int index) { return memory[index]; }
	int getSize() { return size; }
	int getAvaliableSpace() { return capacity - size; }
	void clear();

private:
	int size = 0;
	int capacity;
	WORD* memory;

	bool isFull() { return size >= capacity; }
};