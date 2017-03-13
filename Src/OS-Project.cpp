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
#include <thread>

typedef unsigned long int WORD;   
typedef unsigned char BYTE;

using namespace std;
using namespace std::chrono;

void runCPU(CPU cpu)
{
	cpu.BeginJob();
}

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

		thread cpuThread(runCPU, cpu1);
		cpuThread.join();
		//cpu1.BeginJob();
		count++;
	}

	//print data
	for (int i = 1; i < 31; i++)
	{
		//cout << pcbs.getPCB(i)->stats.completionTime << endl;
		high_resolution_clock::time_point beginTime = pcbs.getPCB(i)->stats.beginTime;
		high_resolution_clock::time_point endTime = pcbs.getPCB(i)->stats.completionTime;

		high_resolution_clock::time_point loadTime = pcbs.getPCB(i)->stats.loadTime;
		high_resolution_clock::time_point completionTime = pcbs.getPCB(i)->stats.completionTime;

		auto duration = duration_cast<microseconds>(endTime - beginTime).count();
		auto waitTime = duration_cast<microseconds>(completionTime-loadTime).count();
		cout << "PCB ID: " << i << endl;
		cout << "Completion Time: " << duration << endl;
		cout << "Wait time: " << waitTime << endl;
		cout << "IO Read Count: " << pcbs.getPCB(i)->stats.ioReadCount << endl;
		cout << "IO Write Count " << pcbs.getPCB(i)->stats.ioWriteCount << endl;
	}


	int test;
	std::cin >> test;

	return 0;
}

