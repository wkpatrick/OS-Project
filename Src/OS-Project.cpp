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
#include "windows.h"
typedef unsigned long int projWORD;   //Because we use windows.h, it includes a version of WORD that is different than ours
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

	LongTermScheduler LTScheduler = LongTermScheduler(&ram, &disk, &pcbs, &readyQ, 0);
	Dispatcher dispatcher = Dispatcher(&readyQ, &pcbs);

	while (!LTScheduler.AllJobsFinished()) {  
		LTScheduler.LoadProcessesToRam();
		dispatcher.Dispatch(&cpu1);
		cpu1.BeginJob();
		count++;
	}

	//print data
	for(int i = 1; i < 31; i++)
		cout << pcbs.getPCB(i)->stats.completionTime << endl;

	//time_t begin = GetTickCount();
	int test;
	std::cin >> test;
	//time_t end = GetTickCount();

	//cout << "Time Diff: " << (end - begin) << endl;
	return 0;
}

