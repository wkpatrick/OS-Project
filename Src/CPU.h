#pragma once
#include <vector>
#include "Memory.h"
#include "PCB.h"
typedef unsigned long int projWORD;
typedef unsigned char BYTE;

using namespace std;

class CPU
{
	projWORD Registers[16]; //16 32 bit registers, Reg[0] is the accumulator, Reg[1] is zero, and the rest are general purpose.
	projWORD ProgramCounter;
	vector<projWORD> InputBuffer;
	vector<projWORD> OutputBuffer;
	vector<projWORD> TempBuffer;
	projWORD inputBufferRamADDR;
	projWORD outputBufferRamADDR;
	projWORD inputBufferRamSize;
	projWORD outputBufferRamSize;
	Memory cpuRAM;
	PCB *pcb;
	int status; //0 for done, 1 for working

public:
	CPU();
	CPU(Memory *ram);
	~CPU();

	int busy; // 0 is idle, 1 is busy
	projWORD GetNextWord();
	void BeginJob();
	void Execute(projWORD word);
	void SetPCB(PCB *_pcb);

private:
	void OPCode00(projWORD opcode);
	void OPCode01(projWORD opcode);
	void OPCode02(projWORD opcode);
	void OPCode03(projWORD opcode);
	void OPCode04(projWORD opcode);
	void OPCode05(projWORD opcode);
	void OPCode06(projWORD opcode);
	void OPCode07(projWORD opcode);
	void OPCode08(projWORD opcode);
	void OPCode09(projWORD opcode);
	void OPCode0A(projWORD opcode);
	void OPCode0B(projWORD opcode);
	void OPCode0C(projWORD opcode);
	void OPCode0D(projWORD opcode);
	void OPCode0E(projWORD opcode);
	void OPCode0F(projWORD opcode);
	void OPCode10(projWORD opcode);
	void OPCode11(projWORD opcode);
	void OPCode12(projWORD opcode);
	void OPCode13(projWORD opcode);
	void OPCode14(projWORD opcode);
	void OPCode15(projWORD opcode);
	void OPCode16(projWORD opcode);
	void OPCode17(projWORD opcode);
	void OPCode18(projWORD opcode);
	void OPCode19(projWORD opcode);
	void OPCode1A(projWORD opcode);
};

