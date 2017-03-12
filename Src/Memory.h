#pragma once
typedef unsigned long int projWORD;

class Memory
{
public:
	Memory(int size);
	Memory();
	~Memory();
	//add a word at the next avaliable location
	void addWord(projWORD word);
	void setWord(int index, projWORD word);
	projWORD getWord(int index) { return memory[index]; }
	int getSize() { return size; }
	int getAvaliableSpace() { return capacity - size; }
	void clear();

private:
	int size = 0;
	int capacity;
	projWORD* memory;

	bool isFull() { return size >= capacity; }
};