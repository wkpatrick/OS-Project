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

