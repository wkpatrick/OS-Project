#include "stdafx.h"
#include "CPU.h"
#include "PCB.h"
#include <iostream>


using namespace std;

CPU::CPU(Memory *ram)
{
	for (int i = 0; i < 16; i++)
	{
		Registers[i] = 0;
	}
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
	cout << "Beginning Job" << endl;
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

	cout << "Ending Job" << endl;

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


	cout << "Opcode: " << opcodeResult << endl;
	switch (opcodeResult)
	{
	case 0:
		OPCode00(opcode);
		break;
	case 1:
		OPCode01(opcode);
		break;
	case 2:
		OPCode02(opcode);
		break;
	case 3:
		OPCode03(opcode);
		break;
	case 4:
		OPCode04(opcode);
		break;
	case 5:
		OPCode05(opcode);
		break;
	case 6:
		OPCode06(opcode);
		break;
	case 7:
		OPCode07(opcode);
		break;
	case 8:
		OPCode08(opcode);
		break;
	case 9:
		OPCode09(opcode);
		break;
	case 10:
		OPCode0A(opcode);
		break;
	case 11:
		OPCode0B(opcode);
		break;
	case 12:
		OPCode0C(opcode);
		break;
	case 13:
		OPCode0D(opcode);
		break;
	case 14:
		OPCode0E(opcode);
		break;
	case 15:
		OPCode0F(opcode);
		break;
	case 16:
		OPCode10(opcode);
		break;
	case 17:
		OPCode11(opcode);
		break;
	case 18:
		OPCode12(opcode);
		break;
	case 19:
		OPCode13(opcode);
		break;
	case 20:
		OPCode14(opcode);
		break;
	case 21:
		OPCode15(opcode);
		break;
	case 22:
		OPCode16(opcode);
		break;
	case 23:
		OPCode17(opcode);
		break;
	case 24:
		OPCode18(opcode);
		break;
	case 25:
		OPCode19(opcode);
		break;
	case 26:
		OPCode1A(opcode);
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

void CPU::OPCode04(WORD opcode) //MOV 
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

	if (Registers[secondSReg != 0])
	{
		Registers[destReg] = Registers[firstSReg] / Registers[secondSReg];
	}
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
	this->status = 0;
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

