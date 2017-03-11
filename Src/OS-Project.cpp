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
#include "Dispatcher.h"
typedef unsigned long int WORD;
typedef unsigned char BYTE;

using namespace std;

int main()
{
	Memory disk = Memory(2048);
	Memory ram = Memory(1024);
	PCBList pcbs = PCBList();
	CPU cpu1 = CPU(&ram);
	int count = 0;

	//queue stores id of PCB
	queue<int> readyQ;

	Loader loader = Loader(&disk, &pcbs);
	loader.load_file();

	LongTermScheduler LTScheduler = LongTermScheduler(&ram, &disk, &pcbs, &readyQ, 1);
	Dispatcher dispatcher = Dispatcher(&readyQ, &pcbs);

	while (!LTScheduler.AllJobsFinished()) {  //Currently gets through 21 or 22 jobs. Gets stuck in a loop then.
		LTScheduler.LoadProcessesToRam();
		dispatcher.Dispatch(&cpu1);
		cpu1.BeginJob();
		count++;
	}

	int test;
	std::cin >> test;
	return 0;
}

