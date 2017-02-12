#pragma once
typedef unsigned long int WORD;
typedef unsigned char BYTE;
class CPU
{
	WORD Registers[16]; //16 32 bit registers, Reg[0] is the accumulator, Reg[1] is zero, and the rest are general purpose.
public:
	CPU();
	~CPU();

	int busy; // 0 is idle, 1 is busy
	void BeginJob();
};

