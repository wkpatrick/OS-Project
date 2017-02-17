#pragma once

enum STATUS
{
	RUNNING,
	READY,
	WAIT,
	NEW,
	TERMINATED,
	TERMINATED_SAVED
};


struct PCB {
	unsigned int cpuID;
	unsigned int pc;	//program counter
	int status;	//STATUS enum used for this
	unsigned int codeSize;
	int priority;	// low # = high priority
	int registers[16];
	int inputBufferSize;
	int outputBufferSize;
	int tempBufferSize;
	unsigned int inputBufferRamAddress;
	unsigned int outputBufferRamAddress;
	unsigned int tempBufferRamAddress;
	unsigned int codeStartDiskAddress;
	unsigned int codeStartRamAddress;
	unsigned int dataStartDiskAddress;
};
