#include "stdafx.h"
#include "CPU.h"
#include "Memory.h"


CPU::CPU(Memory &ram)
{
	memset(Registers, 0, sizeof(Registers));
	busy = 0;
	this->cpuRAM = ram;
}


void CPU::Execute(WORD opcode)
{
	WORD firstTwoBitsMask = 0b11000000000000000000000000000000;
	WORD opcodeBitMask = 0b00111111000000000000000000000000;

	WORD firstTwoBits = (opcode & firstTwoBits) >> 30;
	WORD opcodeResult = (opcode & opcodeBitMask) >> 24;

	switch (firstTwoBits)
	{
	case 0:
	{
		WORD firstSRegBitMask = 0b00000000111100000000000000000000;
		WORD secondSRegBitMask = 0b00000000000011110000000000000000;
		WORD dRegBitMask = 0b00000000000011110000000000000000;

		WORD firstSReg = (opcode & firstSRegBitMask) >> 20;
		WORD secondSReg = (opcode & secondSRegBitMask) >> 16;
		WORD destReg = (opcode & dRegBitMask) >> 12;
	}
		break;
	case 1:
	{
		WORD baseRegBitMask = 0b00000000111100000000000000000000;
		WORD destRegBitMask = 0b00000000000011110000000000000000;
		WORD addressBitMask = 0b00000000000000001111111111111111;

		WORD baseReg = (opcode & baseRegBitMask) >> 20;
		WORD destReg = (opcode & destRegBitMask) >> 16;
		WORD address = (opcode & addressBitMask);
	}
		break;
	case 2:
	{
		WORD addressBitMask = 0b00000000111111111111111111111111;
		WORD adress = (opcode & addressBitMask);
	}
		break;
	case 3:
	{
		WORD regOneBitMask = 0b00000000111100000000000000000000;
		WORD regTwoBitMask = 0b00000000000011110000000000000000;
		WORD addressBitMask = 0b00000000000000001111111111111111;

		WORD regOne = (opcode & regOneBitMask) >> 20;
		WORD regTwo = (opcode & regTwoBitMask) >> 16;
		WORD address = (opcode & addressBitMask);
	}
		break;
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

	Registers[regOne] = InputBuffer.back();
	InputBuffer.pop_back();
}

void CPU::OPCode01(WORD opcode)
{
	WORD regOneBitMask = 0b00000000111100000000000000000000;
	WORD regTwoBitMask = 0b00000000000011110000000000000000;
	WORD addressBitMask = 0b00000000000000001111111111111111;

	WORD regOne = (opcode & regOneBitMask) >> 20;
	WORD regTwo = (opcode & regTwoBitMask) >> 16;
	WORD address = (opcode & addressBitMask);

	InputBuffer.push_back(Registers[regOne]);
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

void CPU::OPCode0B(WORD opcode)
{
}

void CPU::OPCode0C(WORD opcode)
{
}

void CPU::OPCode0D(WORD opcode)
{
}

void CPU::OPCode0E(WORD opcode)
{
}

void CPU::OPCode0F(WORD opcode)
{
}

void CPU::OPCode10(WORD opcode)
{
}

void CPU::OPCode11(WORD opcode)
{
}

void CPU::OPCode12(WORD opcode)
{
}

void CPU::OPCode13(WORD opcode)
{
}

void CPU::OPCode14(WORD opcode)
{
}

void CPU::OPCode15(WORD opcode)
{
}

void CPU::OPCode16(WORD opcode)
{
}

void CPU::OPCode17(WORD opcode)
{
}

void CPU::OPCode18(WORD opcode)
{
}

void CPU::OPCode19(WORD opcode)
{
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

	}
}

