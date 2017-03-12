#include "stdafx.h"
#include "CPU.h"
#include "PCB.h"
#include <iostream>
#include "windows.h"


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


projWORD CPU::GetNextWord()
{
	return cpuRAM.getWord(ProgramCounter);
}

void CPU::BeginJob()
{
	time_t beginTimer;
	cout << "Beginning Job" << endl;
	cout << "PCB Count: " << pcb->pcbCount << endl;

	this->ProgramCounter = pcb->codeStartRamAddress;

	this->inputBufferRamADDR = pcb->inputBufferRamAddress;
	this->inputBufferRamSize = pcb->inputBufferSize;

	this->outputBufferRamADDR = pcb->outputBufferRamAddress;
	this->outputBufferRamSize = pcb->outputBufferSize;

	this->pcb->stats.beginTime = GetTickCount();

	int inputCount = 0;
	int outputCount = 0;
	for (int i = 0; i < 16; i++)
	{
		Registers[i] = pcb->registers[i];
	}

	cout << "Beginning Job at time: " << this->pcb->stats.beginTime << endl;

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

void CPU::Execute(projWORD opcode)
{
	projWORD firstTwoBitsMask = 0b11000000000000000000000000000000;
	projWORD opcodeBitMask = 0b00111111000000000000000000000000;

	projWORD firstTwoBits = (opcode & firstTwoBits) >> 30;
	projWORD opcodeResult = (opcode & opcodeBitMask) >> 24;


	//cout << "Opcode: " << opcodeResult << " First 2 Bits: " << firstTwoBits << endl;
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

void CPU::OPCode00(projWORD opcode) //RD
{
	projWORD regOneBitMask = 0b00000000111100000000000000000000;
	projWORD regTwoBitMask = 0b00000000000011110000000000000000;
	projWORD addressBitMask = 0b00000000000000001111111111111111;

	projWORD regOne = (opcode & regOneBitMask) >> 20;
	projWORD regTwo = (opcode & regTwoBitMask) >> 16;
	projWORD address = (opcode & addressBitMask);

	Registers[0] = cpuRAM.getWord(inputBufferRamADDR);
	inputBufferRamADDR++;
	
}

void CPU::OPCode01(projWORD opcode) //WR
{
	projWORD regOneBitMask = 0b00000000111100000000000000000000;
	projWORD regTwoBitMask = 0b00000000000011110000000000000000;
	projWORD addressBitMask = 0b00000000000000001111111111111111;

	projWORD regOne = (opcode & regOneBitMask) >> 20;
	projWORD regTwo = (opcode & regTwoBitMask) >> 16;
	projWORD address = (opcode & addressBitMask);

	cpuRAM.setWord(outputBufferRamADDR, Registers[0]);
	outputBufferRamADDR++;


}

void CPU::OPCode02(projWORD opcode) //ST
{
	projWORD baseRegBitMask = 0b00000000111100000000000000000000;
	projWORD destRegBitMask = 0b00000000000011110000000000000000;
	projWORD addressBitMask = 0b00000000000000001111111111111111;

	projWORD baseReg = (opcode & baseRegBitMask) >> 20;
	projWORD destReg = (opcode & destRegBitMask) >> 16;
	projWORD address = (opcode & addressBitMask);

	if (destReg == 0)
	{
		cout << "Dest Reg is zero!" << endl;
	}
	cpuRAM.setWord(address, Registers[baseReg]);


}

void CPU::OPCode03(projWORD opcode) //LW
{
	projWORD baseRegBitMask = 0b00000000111100000000000000000000;
	projWORD destRegBitMask = 0b00000000000011110000000000000000;
	projWORD addressBitMask = 0b00000000000000001111111111111111;

	projWORD baseReg = (opcode & baseRegBitMask) >> 20;
	projWORD destReg = (opcode & destRegBitMask) >> 16;
	projWORD address = (opcode & addressBitMask);


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

void CPU::OPCode04(projWORD opcode) //MOV 
{
	projWORD firstSRegBitMask = 0b00000000111100000000000000000000;
	projWORD secondSRegBitMask = 0b00000000000011110000000000000000;
	projWORD dRegBitMask = 0b00000000000000001111000000000000;

	projWORD firstSReg = (opcode & firstSRegBitMask) >> 20;
	projWORD secondSReg = (opcode & secondSRegBitMask) >> 16;
	projWORD destReg = (opcode & dRegBitMask) >> 12;

	Registers[firstSReg] = Registers[secondSReg];
}

void CPU::OPCode05(projWORD opcode) //ADD
{
	projWORD firstSRegBitMask = 0b00000000111100000000000000000000;
	projWORD secondSRegBitMask = 0b00000000000011110000000000000000;
	projWORD dRegBitMask = 0b00000000000000001111000000000000;

	projWORD firstSReg = (opcode & firstSRegBitMask) >> 20;
	projWORD secondSReg = (opcode & secondSRegBitMask) >> 16;
	projWORD destReg = (opcode & dRegBitMask) >> 12;

	Registers[destReg] = Registers[firstSReg] + Registers[secondSReg];
}

void CPU::OPCode06(projWORD opcode) //SUB
{
	projWORD firstSRegBitMask = 0b00000000111100000000000000000000;
	projWORD secondSRegBitMask = 0b00000000000011110000000000000000;
	projWORD dRegBitMask = 0b00000000000000001111000000000000;

	projWORD firstSReg = (opcode & firstSRegBitMask) >> 20;
	projWORD secondSReg = (opcode & secondSRegBitMask) >> 16;
	projWORD destReg = (opcode & dRegBitMask) >> 12;

	Registers[destReg] = Registers[firstSReg] - Registers[secondSReg];
}

void CPU::OPCode07(projWORD opcode) //MULT
{
	projWORD firstSRegBitMask = 0b00000000111100000000000000000000;
	projWORD secondSRegBitMask = 0b00000000000011110000000000000000;
	projWORD dRegBitMask = 0b00000000000000001111000000000000;

	projWORD firstSReg = (opcode & firstSRegBitMask) >> 20;
	projWORD secondSReg = (opcode & secondSRegBitMask) >> 16;
	projWORD destReg = (opcode & dRegBitMask) >> 12;

	Registers[destReg] = Registers[firstSReg] * Registers[secondSReg];
}

void CPU::OPCode08(projWORD opcode) //DIV
{
	projWORD firstSRegBitMask = 0b00000000111100000000000000000000;
	projWORD secondSRegBitMask = 0b00000000000011110000000000000000;
	projWORD dRegBitMask = 0b00000000000000001111000000000000;

	projWORD firstSReg = (opcode & firstSRegBitMask) >> 20;
	projWORD secondSReg = (opcode & secondSRegBitMask) >> 16;
	projWORD destReg = (opcode & dRegBitMask) >> 12;

	if (Registers[secondSReg != 0])
	{
		Registers[destReg] = Registers[firstSReg] / Registers[secondSReg];
	}
}

void CPU::OPCode09(projWORD opcode) //AND
{
	projWORD firstSRegBitMask = 0b00000000111100000000000000000000;
	projWORD secondSRegBitMask = 0b00000000000011110000000000000000;
	projWORD dRegBitMask = 0b00000000000000001111000000000000;

	projWORD firstSReg = (opcode & firstSRegBitMask) >> 20;
	projWORD secondSReg = (opcode & secondSRegBitMask) >> 16;
	projWORD destReg = (opcode & dRegBitMask) >> 12;

	Registers[destReg] = Registers[firstSReg] & Registers[secondSReg];
}

void CPU::OPCode0A(projWORD opcode) //OR
{
	projWORD firstSRegBitMask = 0b00000000111100000000000000000000;
	projWORD secondSRegBitMask = 0b00000000000011110000000000000000;
	projWORD dRegBitMask = 0b00000000000000001111000000000000;

	projWORD firstSReg = (opcode & firstSRegBitMask) >> 20;
	projWORD secondSReg = (opcode & secondSRegBitMask) >> 16;
	projWORD destReg = (opcode & dRegBitMask) >> 12;

	Registers[destReg] = Registers[firstSReg] | Registers[secondSReg];
}

void CPU::OPCode0B(projWORD opcode) //MOVI
{
	projWORD baseRegBitMask = 0b00000000111100000000000000000000;
	projWORD destRegBitMask = 0b00000000000011110000000000000000;
	projWORD addressBitMask = 0b00000000000000001111111111111111;

	projWORD baseReg = (opcode & baseRegBitMask) >> 20;
	projWORD destReg = (opcode & destRegBitMask) >> 16;
	projWORD address = (opcode & addressBitMask);

	Registers[destReg] = cpuRAM.getWord(address);
}

void CPU::OPCode0C(projWORD opcode) //ADDI
{
	projWORD baseRegBitMask = 0b00000000111100000000000000000000;
	projWORD destRegBitMask = 0b00000000000011110000000000000000;
	projWORD addressBitMask = 0b00000000000000001111111111111111;

	projWORD baseReg = (opcode & baseRegBitMask) >> 20;
	projWORD destReg = (opcode & destRegBitMask) >> 16;
	projWORD address = (opcode & addressBitMask);
	
	Registers[destReg] += (cpuRAM.getWord(address) + Registers[baseReg]);

	//Registers[destReg] += cpuRAM.getWord(address);

}

void CPU::OPCode0D(projWORD opcode) //MULTI
{
	projWORD baseRegBitMask = 0b00000000111100000000000000000000;
	projWORD destRegBitMask = 0b00000000000011110000000000000000;
	projWORD addressBitMask = 0b00000000000000001111111111111111;

	projWORD baseReg = (opcode & baseRegBitMask) >> 20;
	projWORD destReg = (opcode & destRegBitMask) >> 16;
	projWORD address = (opcode & addressBitMask);
	//Registers[destReg] = cpuRAM.getWord(address) * Registers[baseReg];
	Registers[destReg] *= cpuRAM.getWord(address);
}

void CPU::OPCode0E(projWORD opcode) //DIVI
{

	projWORD baseRegBitMask = 0b00000000111100000000000000000000;
	projWORD destRegBitMask = 0b00000000000011110000000000000000;
	projWORD addressBitMask = 0b00000000000000001111111111111111;

	projWORD baseReg = (opcode & baseRegBitMask) >> 20;
	projWORD destReg = (opcode & destRegBitMask) >> 16;
	projWORD address = (opcode & addressBitMask);
	if (Registers[baseReg] != 0)
	{
		//Registers[destReg] = cpuRAM.getWord(address)/Registers[baseReg];
		Registers[destReg] = Registers[destReg] / cpuRAM.getWord(address);
	}

}

void CPU::OPCode0F(projWORD opcode)  //LDI
{
	projWORD baseRegBitMask = 0b00000000111100000000000000000000;
	projWORD destRegBitMask = 0b00000000000011110000000000000000;
	projWORD addressBitMask = 0b00000000000000001111111111111111;

	projWORD baseReg = (opcode & baseRegBitMask) >> 20;
	projWORD destReg = (opcode & destRegBitMask) >> 16;
	projWORD address = (opcode & addressBitMask);

	Registers[destReg] = cpuRAM.getWord(address);

}

void CPU::OPCode10(projWORD opcode) //SLT
{
	projWORD firstSRegBitMask = 0b00000000111100000000000000000000;
	projWORD secondSRegBitMask = 0b00000000000011110000000000000000;
	projWORD dRegBitMask = 0b00000000000000001111000000000000;

	projWORD firstSReg = (opcode & firstSRegBitMask) >> 20;
	projWORD secondSReg = (opcode & secondSRegBitMask) >> 16;
	projWORD destReg = (opcode & dRegBitMask) >> 12;

	if (Registers[firstSReg] < Registers[secondSReg])
	{
		Registers[destReg] = 1;
	}
	else
	{
		Registers[destReg] = 0;
	}
}

void CPU::OPCode11(projWORD opcode) //SLTI
{
	projWORD baseRegBitMask = 0b00000000111100000000000000000000;
	projWORD destRegBitMask = 0b00000000000011110000000000000000;
	projWORD addressBitMask = 0b00000000000000001111111111111111;

	projWORD baseReg = (opcode & baseRegBitMask) >> 20;
	projWORD destReg = (opcode & destRegBitMask) >> 16;
	projWORD address = (opcode & addressBitMask);

	if (Registers[baseReg] < address)
	{
		Registers[destReg] = 1;
	}
	else
	{
		Registers[destReg] = 0;
	}
}

void CPU::OPCode12(projWORD opcode) //Halt
{
	time_t endTime;
	this->pcb->stats.completionTime = GetTickCount();
	this->status = 0;
	cout << "Ending Job at time: " << this->pcb->stats.completionTime << endl;
}

void CPU::OPCode13(projWORD opcode) //NOP
{
}

void CPU::OPCode14(projWORD opcode) //JMP
{
	projWORD addressBitMask = 0b00000000111111111111111111111111;
	projWORD address = (opcode & addressBitMask);
	ProgramCounter = address;
}

void CPU::OPCode15(projWORD opcode) //BEQ
{
	projWORD baseRegBitMask = 0b00000000111100000000000000000000;
	projWORD destRegBitMask = 0b00000000000011110000000000000000;
	projWORD addressBitMask = 0b00000000000000001111111111111111;

	projWORD baseReg = (opcode & baseRegBitMask) >> 20;
	projWORD destReg = (opcode & destRegBitMask) >> 16;
	projWORD address = (opcode & addressBitMask);

	if (Registers[baseReg] == Registers[destReg])
	{
		ProgramCounter = address;
	}
}

void CPU::OPCode16(projWORD opcode) //BNE
{
	projWORD baseRegBitMask = 0b00000000111100000000000000000000;
	projWORD destRegBitMask = 0b00000000000011110000000000000000;
	projWORD addressBitMask = 0b00000000000000001111111111111111;

	projWORD baseReg = (opcode & baseRegBitMask) >> 20;
	projWORD destReg = (opcode & destRegBitMask) >> 16;
	projWORD address = (opcode & addressBitMask);

	if (Registers[baseReg] != Registers[destReg])
	{
		ProgramCounter = address;
	}
}

void CPU::OPCode17(projWORD opcode) //BEZ
{
	projWORD baseRegBitMask = 0b00000000111100000000000000000000;
	projWORD destRegBitMask = 0b00000000000011110000000000000000;
	projWORD addressBitMask = 0b00000000000000001111111111111111;

	projWORD baseReg = (opcode & baseRegBitMask) >> 20;
	projWORD destReg = (opcode & destRegBitMask) >> 16;
	projWORD address = (opcode & addressBitMask);

	if (Registers[baseReg] == 0)
	{
		ProgramCounter = address;
	}
}

void CPU::OPCode18(projWORD opcode) //BNZ
{
	projWORD baseRegBitMask = 0b00000000111100000000000000000000;
	projWORD destRegBitMask = 0b00000000000011110000000000000000;
	projWORD addressBitMask = 0b00000000000000001111111111111111;

	projWORD baseReg = (opcode & baseRegBitMask) >> 20;
	projWORD destReg = (opcode & destRegBitMask) >> 16;
	projWORD address = (opcode & addressBitMask);

	if (Registers[baseReg] != 0)
	{
		ProgramCounter = address;
	}
}

void CPU::OPCode19(projWORD opcode) //BGZ
{
	projWORD baseRegBitMask = 0b00000000111100000000000000000000;
	projWORD destRegBitMask = 0b00000000000011110000000000000000;
	projWORD addressBitMask = 0b00000000000000001111111111111111;

	projWORD baseReg = (opcode & baseRegBitMask) >> 20;
	projWORD destReg = (opcode & destRegBitMask) >> 16;
	projWORD address = (opcode & addressBitMask);

	if (Registers[baseReg] > 0)
	{
		ProgramCounter = address;
	}
}

void CPU::OPCode1A(projWORD opcode) //BLZ
{
	projWORD baseRegBitMask = 0b00000000111100000000000000000000;
	projWORD destRegBitMask = 0b00000000000011110000000000000000;
	projWORD addressBitMask = 0b00000000000000001111111111111111;

	projWORD baseReg = (opcode & baseRegBitMask) >> 20;
	projWORD destReg = (opcode & destRegBitMask) >> 16;
	projWORD address = (opcode & addressBitMask);

	if (Registers[baseReg] < 0)
	{
		ProgramCounter = address;
	}
}

