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

private:
	void OPCode00(WORD opcode);
	void OPCode01(WORD opcode);
	void OPCode02(WORD opcode);
	void OPCode03(WORD opcode);
	void OPCode04(WORD opcode);
	void OPCode05(WORD opcode);
	void OPCode06(WORD opcode);
	void OPCode07(WORD opcode);
	void OPCode08(WORD opcode);
	void OPCode09(WORD opcode);
	void OPCode0A(WORD opcode);
	void OPCode0B(WORD opcode);
	void OPCode0C(WORD opcode);
	void OPCode0D(WORD opcode);
	void OPCode0E(WORD opcode);
	void OPCode0F(WORD opcode);
	void OPCode10(WORD opcode);
	void OPCode11(WORD opcode);
	void OPCode12(WORD opcode);
	void OPCode13(WORD opcode);
	void OPCode14(WORD opcode);
	void OPCode15(WORD opcode);
	void OPCode16(WORD opcode);
	void OPCode17(WORD opcode);
	void OPCode18(WORD opcode);
	void OPCode19(WORD opcode);
	void OPCode1A(WORD opcode);
};

