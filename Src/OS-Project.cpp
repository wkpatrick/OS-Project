// OS-Project.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CPU.h"
#include "Memory.h"
#include "PCB.h"
#include "LongTermScheduler.h"
#include "Loader.h"
#include <iostream>
#include <queue>
#include "OS-Project.h"
typedef unsigned long int WORD;
typedef unsigned char BYTE;

using namespace std;

int main()
{
	Memory disk = Memory(2048);
	Memory ram = Memory(1024);
	PCBList pcbs = PCBList();
	CPU cpu1 = CPU(&ram);


	//queue stores id of PCB
	queue<int> readyQ;

	Loader loader = Loader(&disk, &pcbs);
	loader.load_file();

	LongTermScheduler LTScheduler = LongTermScheduler(&ram, &disk, &pcbs, &readyQ);

	while (!LTScheduler.AllJobsFinished()) {
		LTScheduler.LoadProcessesToRam();
		cpu1.BeginJob(pcbs.getPCB(1));
		//dispatch stuff
		//cpu stuff
	}

	int test;
	std::cin >> test;
	return 0;
}

