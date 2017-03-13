#include "stdafx.h"
#include "CPU.h"
#include "PCB.h"
#include <iostream>
#include <chrono>


using namespace std;
using namespace std::chrono;

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
	//delete [] Registers;
}


WORD CPU::GetNextWord()
{
	return cpuRAM.getWord(ProgramCounter);
}

void CPU::BeginJob()
{
	//cout << "Beginning Job" << endl;
	//cout << "PCB Count: " << pcb->pcbCount << endl;

	this->ProgramCounter = pcb->codeStartRamAddress;

	this->inputBufferRamADDR = pcb->inputBufferRamAddress;
	this->inputBufferRamSize = pcb->inputBufferSize;

	this->outputBufferRamADDR = pcb->outputBufferRamAddress;
	this->outputBufferRamSize = pcb->outputBufferSize;

	this->pcb->stats.beginTime = high_resolution_clock::now();

	int inputCount = 0;
	int outputCount = 0;
	for (int i = 0; i < 16; i++)
	{
		Registers[i] = pcb->registers[i];
	}

	//cout << "Beginning Job at time: " << this->pcb->stats.beginTime << endl;

	status = 1;
	while (status == 1)
	{
		Execute(GetNextWord());
		Registers[1] = 0;   //To ensure that Reg 1 stays 0
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


	//cout << "Opcode: " << opcodeResult << " First 2 Bits: " << firstTwoBits << endl;
	switch (opcodeResult)
	{
	case 0:
		OPCode00(opcode);
		this->pcb->stats.ioReadCount++;
		break;
	case 1:
		OPCode01(opcode);
		this->pcb->stats.ioWriteCount++;
		break;
	case 2:
		OPCode02(opcode);
		this->pcb->stats.ioWriteCount++;
		break;
	case 3:
		OPCode03(opcode);
		this->pcb->stats.ioReadCount++;
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
		this->pcb->stats.ioReadCount++;
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
		this->pcb->stats.ioReadCount++;
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

void CPU::OPCode00(WORD opcode) //RD
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

void CPU::OPCode01(WORD opcode) //WR
{
	WORD regOneBitMask = 0b00000000111100000000000000000000;
	WORD regTwoBitMask = 0b00000000000011110000000000000000;
	WORD addressBitMask = 0b00000000000000001111111111111111;

	WORD regOne = (opcode & regOneBitMask) >> 20;
	WORD regTwo = (opcode & regTwoBitMask) >> 16;
	WORD address = (opcode & addressBitMask);

	cpuRAM.setWord(outputBufferRamADDR, Registers[0]);
	outputBufferRamADDR++;
}

void CPU::OPCode02(WORD opcode) //ST
{
	WORD baseRegBitMask = 0b00000000111100000000000000000000;
	WORD destRegBitMask = 0b00000000000011110000000000000000;
	WORD addressBitMask = 0b00000000000000001111111111111111;

	WORD baseReg = (opcode & baseRegBitMask) >> 20;
	WORD destReg = (opcode & destRegBitMask) >> 16;
	WORD address = (opcode & addressBitMask);

	if (destReg == 0)
	{
		cout << "Dest Reg is zero!" << endl;
	}
	cpuRAM.setWord(address, Registers[baseReg]);


}

void CPU::OPCode03(WORD opcode) //LW
{
	WORD baseRegBitMask = 0b00000000111100000000000000000000;
	WORD destRegBitMask = 0b00000000000011110000000000000000;
	WORD addressBitMask = 0b00000000000000001111111111111111;

	WORD baseReg = (opcode & baseRegBitMask) >> 20;
	WORD destReg = (opcode & destRegBitMask) >> 16;
	WORD address = (opcode & addressBitMask);


	if (address == 0)
	{
		Registers[destReg] = Registers[baseReg];
	}
	else
	{
		Registers[destReg] = cpuRAM.getWord(address);
	}
	//Registers[destReg] = cpuRAM.getWord(Registers[baseReg] + address);     Try baseReg + address????
}

void CPU::OPCode04(WORD opcode) //MOV 
{
	WORD firstSRegBitMask = 0b00000000111100000000000000000000;
	WORD secondSRegBitMask = 0b00000000000011110000000000000000;
	WORD dRegBitMask = 0b00000000000000001111000000000000;

	WORD firstSReg = (opcode & firstSRegBitMask) >> 20;
	WORD secondSReg = (opcode & secondSRegBitMask) >> 16;
	WORD destReg = (opcode & dRegBitMask) >> 12;

	Registers[firstSReg] = Registers[secondSReg];
}

void CPU::OPCode05(WORD opcode) //ADD
{
	WORD firstSRegBitMask = 0b00000000111100000000000000000000;
	WORD secondSRegBitMask = 0b00000000000011110000000000000000;
	WORD dRegBitMask = 0b00000000000000001111000000000000;

	WORD firstSReg = (opcode & firstSRegBitMask) >> 20;
	WORD secondSReg = (opcode & secondSRegBitMask) >> 16;
	WORD destReg = (opcode & dRegBitMask) >> 12;

	Registers[destReg] = Registers[firstSReg] + Registers[secondSReg];
}

void CPU::OPCode06(WORD opcode) //SUB
{
	WORD firstSRegBitMask = 0b00000000111100000000000000000000;
	WORD secondSRegBitMask = 0b00000000000011110000000000000000;
	WORD dRegBitMask = 0b00000000000000001111000000000000;

	WORD firstSReg = (opcode & firstSRegBitMask) >> 20;
	WORD secondSReg = (opcode & secondSRegBitMask) >> 16;
	WORD destReg = (opcode & dRegBitMask) >> 12;

	Registers[destReg] = Registers[firstSReg] - Registers[secondSReg];
}

void CPU::OPCode07(WORD opcode) //MULT
{
	WORD firstSRegBitMask = 0b00000000111100000000000000000000;
	WORD secondSRegBitMask = 0b00000000000011110000000000000000;
	WORD dRegBitMask = 0b00000000000000001111000000000000;

	WORD firstSReg = (opcode & firstSRegBitMask) >> 20;
	WORD secondSReg = (opcode & secondSRegBitMask) >> 16;
	WORD destReg = (opcode & dRegBitMask) >> 12;

	Registers[destReg] = Registers[firstSReg] * Registers[secondSReg];
}

void CPU::OPCode08(WORD opcode) //DIV
{
	WORD firstSRegBitMask = 0b00000000111100000000000000000000;
	WORD secondSRegBitMask = 0b00000000000011110000000000000000;
	WORD dRegBitMask = 0b00000000000000001111000000000000;

	WORD firstSReg = (opcode & firstSRegBitMask) >> 20;
	WORD secondSReg = (opcode & secondSRegBitMask) >> 16;
	WORD destReg = (opcode & dRegBitMask) >> 12;

	if (Registers[secondSReg != 0])
	{
		Registers[destReg] = Registers[firstSReg] / Registers[secondSReg];
	}
}

void CPU::OPCode09(WORD opcode) //AND
{
	WORD firstSRegBitMask = 0b00000000111100000000000000000000;
	WORD secondSRegBitMask = 0b00000000000011110000000000000000;
	WORD dRegBitMask = 0b00000000000000001111000000000000;

	WORD firstSReg = (opcode & firstSRegBitMask) >> 20;
	WORD secondSReg = (opcode & secondSRegBitMask) >> 16;
	WORD destReg = (opcode & dRegBitMask) >> 12;

	Registers[destReg] = Registers[firstSReg] & Registers[secondSReg];
}

void CPU::OPCode0A(WORD opcode) //OR
{
	WORD firstSRegBitMask = 0b00000000111100000000000000000000;
	WORD secondSRegBitMask = 0b00000000000011110000000000000000;
	WORD dRegBitMask = 0b00000000000000001111000000000000;

	WORD firstSReg = (opcode & firstSRegBitMask) >> 20;
	WORD secondSReg = (opcode & secondSRegBitMask) >> 16;
	WORD destReg = (opcode & dRegBitMask) >> 12;

	Registers[destReg] = Registers[firstSReg] | Registers[secondSReg];
}

void CPU::OPCode0B(WORD opcode) //MOVI
{
	WORD baseRegBitMask = 0b00000000111100000000000000000000;
	WORD destRegBitMask = 0b00000000000011110000000000000000;
	WORD addressBitMask = 0b00000000000000001111111111111111;

	WORD baseReg = (opcode & baseRegBitMask) >> 20;
	WORD destReg = (opcode & destRegBitMask) >> 16;
	WORD address = (opcode & addressBitMask);

	Registers[destReg] = cpuRAM.getWord(address);
}

void CPU::OPCode0C(WORD opcode) //ADDI
{
	WORD baseRegBitMask = 0b00000000111100000000000000000000;
	WORD destRegBitMask = 0b00000000000011110000000000000000;
	WORD addressBitMask = 0b00000000000000001111111111111111;

	WORD baseReg = (opcode & baseRegBitMask) >> 20;
	WORD destReg = (opcode & destRegBitMask) >> 16;
	WORD address = (opcode & addressBitMask);
	
	Registers[destReg] += (cpuRAM.getWord(address) + Registers[baseReg]);

	//Registers[destReg] += cpuRAM.getWord(address);

}

void CPU::OPCode0D(WORD opcode) //MULTI
{
	WORD baseRegBitMask = 0b00000000111100000000000000000000;
	WORD destRegBitMask = 0b00000000000011110000000000000000;
	WORD addressBitMask = 0b00000000000000001111111111111111;

	WORD baseReg = (opcode & baseRegBitMask) >> 20;
	WORD destReg = (opcode & destRegBitMask) >> 16;
	WORD address = (opcode & addressBitMask);
	//Registers[destReg] = cpuRAM.getWord(address) * Registers[baseReg];
	Registers[destReg] *= cpuRAM.getWord(address);
}

void CPU::OPCode0E(WORD opcode) //DIVI
{

	WORD baseRegBitMask = 0b00000000111100000000000000000000;
	WORD destRegBitMask = 0b00000000000011110000000000000000;
	WORD addressBitMask = 0b00000000000000001111111111111111;

	WORD baseReg = (opcode & baseRegBitMask) >> 20;
	WORD destReg = (opcode & destRegBitMask) >> 16;
	WORD address = (opcode & addressBitMask);
	if (Registers[baseReg] != 0)
	{
		//Registers[destReg] = cpuRAM.getWord(address)/Registers[baseReg];
		Registers[destReg] = Registers[destReg] / cpuRAM.getWord(address);
	}

}

void CPU::OPCode0F(WORD opcode)  //LDI
{
	WORD baseRegBitMask = 0b00000000111100000000000000000000;
	WORD destRegBitMask = 0b00000000000011110000000000000000;
	WORD addressBitMask = 0b00000000000000001111111111111111;

	WORD baseReg = (opcode & baseRegBitMask) >> 20;
	WORD destReg = (opcode & destRegBitMask) >> 16;
	WORD address = (opcode & addressBitMask);

	Registers[destReg] = cpuRAM.getWord(address);

}

void CPU::OPCode10(WORD opcode) //SLT
{
	WORD firstSRegBitMask = 0b00000000111100000000000000000000;
	WORD secondSRegBitMask = 0b00000000000011110000000000000000;
	WORD dRegBitMask = 0b00000000000000001111000000000000;

	WORD firstSReg = (opcode & firstSRegBitMask) >> 20;
	WORD secondSReg = (opcode & secondSRegBitMask) >> 16;
	WORD destReg = (opcode & dRegBitMask) >> 12;

	if (Registers[firstSReg] < Registers[secondSReg])
	{
		Registers[destReg] = 1;
	}
	else
	{
		Registers[destReg] = 0;
	}
}

void CPU::OPCode11(WORD opcode) //SLTI
{
	WORD baseRegBitMask = 0b00000000111100000000000000000000;
	WORD destRegBitMask = 0b00000000000011110000000000000000;
	WORD addressBitMask = 0b00000000000000001111111111111111;

	WORD baseReg = (opcode & baseRegBitMask) >> 20;
	WORD destReg = (opcode & destRegBitMask) >> 16;
	WORD address = (opcode & addressBitMask);

	if (Registers[baseReg] < address)
	{
		Registers[destReg] = 1;
	}
	else
	{
		Registers[destReg] = 0;
	}
}

void CPU::OPCode12(WORD opcode) //Halt
{
	this->pcb->stats.completionTime = high_resolution_clock::now();
	this->status = 0;
	//cout << "Ending Job at time: " << this->pcb->stats.completionTime << endl;
}

void CPU::OPCode13(WORD opcode) //NOP
{
}

void CPU::OPCode14(WORD opcode) //JMP
{
	WORD addressBitMask = 0b00000000111111111111111111111111;
	WORD address = (opcode & addressBitMask);
	ProgramCounter = address;
}

void CPU::OPCode15(WORD opcode) //BEQ
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

void CPU::OPCode16(WORD opcode) //BNE
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

void CPU::OPCode17(WORD opcode) //BEZ
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

void CPU::OPCode18(WORD opcode) //BNZ
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

void CPU::OPCode19(WORD opcode) //BGZ
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

void CPU::OPCode1A(WORD opcode) //BLZ
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

