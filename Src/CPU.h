#pragma once
#include <vector>
typedef unsigned long int WORD;
typedef unsigned char BYTE;

using namespace std;
class CPU
{
	WORD Registers[16]; //16 32 bit registers, Reg[0] is the accumulator, Reg[1] is zero, and the rest are general purpose.
	WORD ProgramCounter;
	vector<WORD> InputBuffer;
	vector<WORD> OutputBuffer;
	vector<WORD> TempBuffer;

public:
	CPU();
	~CPU();

	int busy; // 0 is idle, 1 is busy
	void BeginJob();
	WORD GetNextWord();
	void Execute(WORD word);

};

