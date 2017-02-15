#include "stdafx.h"
#include "CPU.h"


CPU::CPU()
{
	memset(Registers, 0, sizeof(Registers));
	busy = 0;
}


CPU::~CPU()
{
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
		WORD firstSRegBitMask = 0b00000000111100000000000000000000;
		WORD secondSRegBitMask = 0b00000000000011110000000000000000;
		WORD dRegBitMask = 0b00000000000011110000000000000000;

		WORD firstSReg = (opcode & firstSRegBitMask) >> 20;
		WORD secondSReg = (opcode & secondSRegBitMask) >> 16;
		WORD destReg = (opcode & dRegBitMask) >> 12;

		break;
	case 1:
		WORD baseRegBitMask = 0b00000000111100000000000000000000;
		WORD destRegBitMask = 0b00000000000011110000000000000000;
		WORD addressBitMask = 0b00000000000000001111111111111111;

		WORD baseReg = (opcode & baseRegBitMask) >> 20;
		WORD destReg = (opcode & destRegBitMask) >> 16;
		WORD address = (opcode & addressBitMask);
		break;
	case 2:
		break;
	case 3:
		break;
	}

}

