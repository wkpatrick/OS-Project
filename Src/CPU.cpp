#include "stdafx.h"
#include "CPU.h"
#include "Memory.h"
#include "PCB.h"
#include <iostream>


using namespace std;

CPU::CPU(Memory *ram)
{
	memset(Registers, 0, sizeof(Registers));
	busy = 0;
	this->cpuRAM = *ram;
}

CPU::~CPU()
{
	delete[] Registers;
}


WORD CPU::GetNextWord()
{
	return cpuRAM.getWord(ProgramCounter);
}

void CPU::BeginJob()
{

	//std::cout << "input ram size " << pcb->inputBufferSize << endl;
	std::cout << "Ram Start Address. " << pcb->codeStartRamAddress << endl;
	std::cout << "Data start Ram Address " << pcb->dataStartDiskAddress << endl;
	this->ProgramCounter = pcb->codeStartRamAddress;

	this->inputBufferRamADDR = pcb->inputBufferRamAddress;
	this->inputBufferRamSize = pcb->inputBufferSize;

	this->outputBufferRamADDR = pcb->outputBufferRamAddress;
	this->outputBufferRamSize = pcb->outputBufferSize;
	for (int i = 0; i < 16; i++)
	{
		Registers[i] = pcb->registers[i];
	}

	status = 1;
	while (status == 1)
	{
		Execute(GetNextWord());
		ProgramCounter++;
	}


}

void CPU::SetPCB(PCB * _pcb)
{
	pcb = _pcb;
}

void CPU::Execute(WORD opcode)
{
	WORD firstTwoBitsMask = 0b11000000000000000000000000000000;
	WORD opcodeBitMask = 0b00111111000000000000000000000000;

	WORD firstTwoBits = (opcode & firstTwoBits) >> 30;
	WORD opcodeResult = (opcode & opcodeBitMask) >> 24;

	switch (opcode)
	{
	case 0:
		OPCode00(opcode);
	case 1:
		OPCode01(opcode);
	case 2:
		OPCode02(opcode);
	case 3:
		OPCode03(opcode);
	case 4:
		OPCode04(opcode);
	case 5:
		OPCode05(opcode);
	case 6:
		OPCode06(opcode);
	case 7:
		OPCode07(opcode);
	case 8:
		OPCode09(opcode);
	case 9:
		OPCode0A(opcode);
	case 10:
		OPCode0B(opcode);
	case 11:
		OPCode0C(opcode);
	case 12:
		OPCode0D(opcode);
	case 13:
		OPCode0E(opcode);
	case 14:
		OPCode0F(opcode);
	case 15:
		OPCode11(opcode);
	case 16:
		OPCode12(opcode);
	case 17:
		OPCode13(opcode);
	case 18:
		OPCode14(opcode);
	case 19:
		OPCode15(opcode);
	case 20:
		OPCode16(opcode);
	case 21:
		OPCode17(opcode);
	case 22:
		OPCode18(opcode);
	case 23:
		OPCode19(opcode);
	case 24:
		OPCode1A(opcode);
	}

}

void CPU::OPCode00(WORD opcode)
{
	WORD regOneBitMask = 0b00000000111100000000000000000000;
	WORD regTwoBitMask = 0b00000000000011110000000000000000;
	WORD addressBitMask = 0b00000000000000001111111111111111;

	WORD regOne = (opcode & regOneBitMask) >> 20;
	WORD regTwo = (opcode & regTwoBitMask) >> 16;
	WORD address = (opcode & addressBitMask);

	Registers[0] = cpuRAM.getWord(inputBufferRamADDR);
	inputBufferRamADDR++;
	
}

void CPU::OPCode01(WORD opcode)
{
	WORD regOneBitMask = 0b00000000111100000000000000000000;
	WORD regTwoBitMask = 0b00000000000011110000000000000000;
	WORD addressBitMask = 0b00000000000000001111111111111111;

	WORD regOne = (opcode & regOneBitMask) >> 20;
	WORD regTwo = (opcode & regTwoBitMask) >> 16;
	WORD address = (opcode & addressBitMask);
	
	cpuRAM.setWord(address, Registers[0]);

}

void CPU::OPCode02(WORD opcode) //Stores the contents of baseReg in address
{
	WORD baseRegBitMask = 0b00000000111100000000000000000000;
	WORD destRegBitMask = 0b00000000000011110000000000000000;
	WORD addressBitMask = 0b00000000000000001111111111111111;

	WORD baseReg = (opcode & baseRegBitMask) >> 20;
	WORD destReg = (opcode & destRegBitMask) >> 16;
	WORD address = (opcode & addressBitMask);

	cpuRAM.setWord(address, Registers[baseReg]);


}

void CPU::OPCode03(WORD opcode) //Loads the contents of address into basereg
{
	WORD baseRegBitMask = 0b00000000111100000000000000000000;
	WORD destRegBitMask = 0b00000000000011110000000000000000;
	WORD addressBitMask = 0b00000000000000001111111111111111;

	WORD baseReg = (opcode & baseRegBitMask) >> 20;
	WORD destReg = (opcode & destRegBitMask) >> 16;
	WORD address = (opcode & addressBitMask);

	Registers[baseReg] = cpuRAM.getWord(address);
}

void CPU::OPCode04(WORD opcode)
{

}

void CPU::OPCode05(WORD opcode)
{
	WORD firstSRegBitMask = 0b00000000111100000000000000000000;
	WORD secondSRegBitMask = 0b00000000000011110000000000000000;
	WORD dRegBitMask = 0b00000000000011110000000000000000;

	WORD firstSReg = (opcode & firstSRegBitMask) >> 20;
	WORD secondSReg = (opcode & secondSRegBitMask) >> 16;
	WORD destReg = (opcode & dRegBitMask) >> 12;

	Registers[destReg] = Registers[firstSReg] + Registers[secondSReg];
}

void CPU::OPCode06(WORD opcode)
{
	WORD firstSRegBitMask = 0b00000000111100000000000000000000;
	WORD secondSRegBitMask = 0b00000000000011110000000000000000;
	WORD dRegBitMask = 0b00000000000011110000000000000000;

	WORD firstSReg = (opcode & firstSRegBitMask) >> 20;
	WORD secondSReg = (opcode & secondSRegBitMask) >> 16;
	WORD destReg = (opcode & dRegBitMask) >> 12;

	Registers[destReg] = Registers[firstSReg] - Registers[secondSReg];
}

void CPU::OPCode07(WORD opcode)
{
	WORD firstSRegBitMask = 0b00000000111100000000000000000000;
	WORD secondSRegBitMask = 0b00000000000011110000000000000000;
	WORD dRegBitMask = 0b00000000000011110000000000000000;

	WORD firstSReg = (opcode & firstSRegBitMask) >> 20;
	WORD secondSReg = (opcode & secondSRegBitMask) >> 16;
	WORD destReg = (opcode & dRegBitMask) >> 12;

	Registers[destReg] = Registers[firstSReg] * Registers[secondSReg];
}

void CPU::OPCode08(WORD opcode)
{
	WORD firstSRegBitMask = 0b00000000111100000000000000000000;
	WORD secondSRegBitMask = 0b00000000000011110000000000000000;
	WORD dRegBitMask = 0b00000000000011110000000000000000;

	WORD firstSReg = (opcode & firstSRegBitMask) >> 20;
	WORD secondSReg = (opcode & secondSRegBitMask) >> 16;
	WORD destReg = (opcode & dRegBitMask) >> 12;

	Registers[destReg] = Registers[firstSReg] / Registers[secondSReg];
}

void CPU::OPCode09(WORD opcode)
{
	WORD firstSRegBitMask = 0b00000000111100000000000000000000;
	WORD secondSRegBitMask = 0b00000000000011110000000000000000;
	WORD dRegBitMask = 0b00000000000011110000000000000000;

	WORD firstSReg = (opcode & firstSRegBitMask) >> 20;
	WORD secondSReg = (opcode & secondSRegBitMask) >> 16;
	WORD destReg = (opcode & dRegBitMask) >> 12;

	Registers[destReg] = Registers[firstSReg] & Registers[secondSReg];
}

void CPU::OPCode0A(WORD opcode)
{
	WORD firstSRegBitMask = 0b00000000111100000000000000000000;
	WORD secondSRegBitMask = 0b00000000000011110000000000000000;
	WORD dRegBitMask = 0b00000000000011110000000000000000;

	WORD firstSReg = (opcode & firstSRegBitMask) >> 20;
	WORD secondSReg = (opcode & secondSRegBitMask) >> 16;
	WORD destReg = (opcode & dRegBitMask) >> 12;

	Registers[destReg] = Registers[firstSReg] | Registers[secondSReg];
}

void CPU::OPCode0B(WORD opcode) // Possibly uses indirect addressing. Test!
{
	WORD baseRegBitMask = 0b00000000111100000000000000000000;
	WORD destRegBitMask = 0b00000000000011110000000000000000;
	WORD addressBitMask = 0b00000000000000001111111111111111;

	WORD baseReg = (opcode & baseRegBitMask) >> 20;
	WORD destReg = (opcode & destRegBitMask) >> 16;
	WORD address = (opcode & addressBitMask);
	Registers[destReg] = cpuRAM.getWord(address);
}

void CPU::OPCode0C(WORD opcode)
{
	WORD baseRegBitMask = 0b00000000111100000000000000000000;
	WORD destRegBitMask = 0b00000000000011110000000000000000;
	WORD addressBitMask = 0b00000000000000001111111111111111;

	WORD baseReg = (opcode & baseRegBitMask) >> 20;
	WORD destReg = (opcode & destRegBitMask) >> 16;
	WORD address = (opcode & addressBitMask);
	Registers[destReg] = cpuRAM.getWord(address) + Registers[baseReg];
}

void CPU::OPCode0D(WORD opcode) //Multiplies what into the register. TEST!
{
	WORD baseRegBitMask = 0b00000000111100000000000000000000;
	WORD destRegBitMask = 0b00000000000011110000000000000000;
	WORD addressBitMask = 0b00000000000000001111111111111111;

	WORD baseReg = (opcode & baseRegBitMask) >> 20;
	WORD destReg = (opcode & destRegBitMask) >> 16;
	WORD address = (opcode & addressBitMask);
	Registers[destReg] = cpuRAM.getWord(address) * Registers[baseReg];
}

void CPU::OPCode0E(WORD opcode) //Divides what into the register. TEST!
{

	WORD baseRegBitMask = 0b00000000111100000000000000000000;
	WORD destRegBitMask = 0b00000000000011110000000000000000;
	WORD addressBitMask = 0b00000000000000001111111111111111;

	WORD baseReg = (opcode & baseRegBitMask) >> 20;
	WORD destReg = (opcode & destRegBitMask) >> 16;
	WORD address = (opcode & addressBitMask);
	if(Registers[baseReg] != 0)
		Registers[destReg] = cpuRAM.getWord(address)/Registers[baseReg];
}

void CPU::OPCode0F(WORD opcode)
{
	WORD regOneBitMask = 0b00000000111100000000000000000000;
	WORD regTwoBitMask = 0b00000000000011110000000000000000;
	WORD addressBitMask = 0b00000000000000001111111111111111;

	WORD regOne = (opcode & regOneBitMask) >> 20;
	WORD regTwo = (opcode & regTwoBitMask) >> 16;
	WORD address = (opcode & addressBitMask);
	Registers[regOne] = cpuRAM.getWord(address);

}

void CPU::OPCode10(WORD opcode)
{
}

void CPU::OPCode11(WORD opcode)
{
	WORD baseRegBitMask = 0b00000000111100000000000000000000;
	WORD destRegBitMask = 0b00000000000011110000000000000000;
	WORD addressBitMask = 0b00000000000000001111111111111111;

	WORD baseReg = (opcode & baseRegBitMask) >> 20;
	WORD destReg = (opcode & destRegBitMask) >> 16;
	WORD address = (opcode & addressBitMask);

}

void CPU::OPCode12(WORD opcode) //Halt
{
	status = 0;
}

void CPU::OPCode13(WORD opcode) //NOP
{
}

void CPU::OPCode14(WORD opcode)
{
	WORD addressBitMask = 0b00000000111111111111111111111111;
	WORD address = (opcode & addressBitMask);
	ProgramCounter = address;
}

void CPU::OPCode15(WORD opcode)
{
	WORD baseRegBitMask = 0b00000000111100000000000000000000;
	WORD destRegBitMask = 0b00000000000011110000000000000000;
	WORD addressBitMask = 0b00000000000000001111111111111111;

	WORD baseReg = (opcode & baseRegBitMask) >> 20;
	WORD destReg = (opcode & destRegBitMask) >> 16;
	WORD address = (opcode & addressBitMask);

	if (Registers[baseReg] == Registers[destReg])
	{
		ProgramCounter = address;
	}
}

void CPU::OPCode16(WORD opcode)
{
	WORD baseRegBitMask = 0b00000000111100000000000000000000;
	WORD destRegBitMask = 0b00000000000011110000000000000000;
	WORD addressBitMask = 0b00000000000000001111111111111111;

	WORD baseReg = (opcode & baseRegBitMask) >> 20;
	WORD destReg = (opcode & destRegBitMask) >> 16;
	WORD address = (opcode & addressBitMask);

	if (Registers[baseReg] != Registers[destReg])
	{
		ProgramCounter = address;
	}
}

void CPU::OPCode17(WORD opcode)
{
	WORD baseRegBitMask = 0b00000000111100000000000000000000;
	WORD destRegBitMask = 0b00000000000011110000000000000000;
	WORD addressBitMask = 0b00000000000000001111111111111111;

	WORD baseReg = (opcode & baseRegBitMask) >> 20;
	WORD destReg = (opcode & destRegBitMask) >> 16;
	WORD address = (opcode & addressBitMask);

	if (Registers[baseReg] == 0)
	{
		ProgramCounter = address;
	}
}

void CPU::OPCode18(WORD opcode)
{
	WORD baseRegBitMask = 0b00000000111100000000000000000000;
	WORD destRegBitMask = 0b00000000000011110000000000000000;
	WORD addressBitMask = 0b00000000000000001111111111111111;

	WORD baseReg = (opcode & baseRegBitMask) >> 20;
	WORD destReg = (opcode & destRegBitMask) >> 16;
	WORD address = (opcode & addressBitMask);

	if (Registers[baseReg] != 0)
	{
		ProgramCounter = address;
	}
}

void CPU::OPCode19(WORD opcode)
{
	WORD baseRegBitMask = 0b00000000111100000000000000000000;
	WORD destRegBitMask = 0b00000000000011110000000000000000;
	WORD addressBitMask = 0b00000000000000001111111111111111;

	WORD baseReg = (opcode & baseRegBitMask) >> 20;
	WORD destReg = (opcode & destRegBitMask) >> 16;
	WORD address = (opcode & addressBitMask);

	if (Registers[baseReg] > 0)
	{
		ProgramCounter = address;
	}
}

void CPU::OPCode1A(WORD opcode)
{
	WORD baseRegBitMask = 0b00000000111100000000000000000000;
	WORD destRegBitMask = 0b00000000000011110000000000000000;
	WORD addressBitMask = 0b00000000000000001111111111111111;

	WORD baseReg = (opcode & baseRegBitMask) >> 20;
	WORD destReg = (opcode & destRegBitMask) >> 16;
	WORD address = (opcode & addressBitMask);

	if (Registers[baseReg] < 0)
	{
		ProgramCounter = address;
	}
}

