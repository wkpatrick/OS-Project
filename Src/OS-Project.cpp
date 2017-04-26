// OS-Project.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CPU.h"
#include "Memory.h"
#include "PCB.h"
#include "LongTermScheduler.h"
#include "Loader.h"
#include <iostream>
#include "OS-Project.h"
#include "Dispatcher.h"
#include <thread>
#include <mutex>
#include <vector>
#include <iostream>
#include <fstream>

typedef unsigned long int WORD;   
typedef unsigned char BYTE;

using namespace std;
using namespace std::chrono;

mutex ramLock;
mutex readyQDispatchLock;

void runCPU(CPU *cpu, int id)
{
	cpu->BeginJob(id);
}


int main()
{
	Memory disk = Memory(2048);
	Memory ram = Memory(1024);
	PCBList pcbs = PCBList();
	vector<WORD> history;

	CPU cpu1 = CPU(&ram);
	CPU cpu2 = CPU(&ram);
	CPU cpu3 = CPU(&ram);
	CPU cpu4 = CPU(&ram);

	int count = 0;

	//queue stores id of PCB
	queue<int> readyQ;

	Loader loader = Loader(&disk, &pcbs);
	loader.load_file();

	LongTermScheduler LTScheduler = LongTermScheduler(&ram, &disk, &pcbs, &readyQ, 0);
	Dispatcher dispatcher = Dispatcher(&readyQ, &pcbs);

	while (!LTScheduler.AllJobsFinished()) {  
		LTScheduler.LoadProcessesToRam();

		ramLock.lock();
		dispatcher.Dispatch(&cpu1);
		dispatcher.Dispatch(&cpu2);
		dispatcher.Dispatch(&cpu3);
		dispatcher.Dispatch(&cpu4);


		thread cpuThread1(runCPU, &cpu1, 1);
		thread cpuThread2(runCPU, &cpu2, 2);
		thread cpuThread3(runCPU, &cpu3, 3);
		thread cpuThread4(runCPU, &cpu4, 4);

		if (cpuThread1.joinable())
		{
			cpuThread1.join();
		}
		if (cpuThread2.joinable())
		{
			cpuThread2.join();
		}

		if (cpuThread3.joinable())
		{
			cpuThread3.join();
		}

		if (cpuThread4.joinable())
		{
			cpuThread4.join();
		}

		ramLock.unlock();
		ramLock.lock();



		PageTable cacheOne = cpu1.getCacheTable();
		PageTable cacheTwo = cpu2.getCacheTable();
		PageTable cacheThree = cpu3.getCacheTable();
		PageTable cacheFour = cpu4.getCacheTable();

		for (int i = 0; i < cpu1.getCacheSize(); i++)
		{
			history.push_back(cacheOne.getNoPageWord(i));
		}
		for (int i = 0; i < cpu2.getCacheSize(); i++)
		{
			history.push_back(cacheTwo.getNoPageWord(i));
		}
		for (int i = 0; i < cpu3.getCacheSize(); i++)
		{
			history.push_back(cacheThree.getNoPageWord(i));
		}
		for (int i = 0; i < cpu4.getCacheSize(); i++)
		{
			history.push_back(cacheFour.getNoPageWord(i));
		}

		ramLock.unlock();



		//dispatcher.Dispatch(&cpu1);
		//cpu1.BeginJob();
		count++;
	}

	ofstream myfile;
	myfile.open("RamDumpNew.txt");
	for (int i = 0; i < history.size(); i++) {
		myfile << "0x" << hex << history.at(i) << "\n";
	}
	myfile.close();

	//print data
	for (int i = 1; i < 31; i++)
	{
		high_resolution_clock::time_point beginTime = pcbs.getPCB(i)->stats.beginTime;
		high_resolution_clock::time_point endTime = pcbs.getPCB(i)->stats.completionTime;

		high_resolution_clock::time_point loadTime = pcbs.getPCB(i)->stats.loadTime;
		high_resolution_clock::time_point completionTime = pcbs.getPCB(i)->stats.completionTime;

		auto duration = duration_cast<microseconds>(endTime - beginTime).count();
		auto waitTime = duration_cast<microseconds>(completionTime-loadTime).count();
		cout << "PCB ID: " << i << endl;

		cout << "Wait time: " << waitTime << endl;
		cout << "Completion Time: " << duration << endl;
		cout << "IO Read Count: " << pcbs.getPCB(i)->stats.ioReadCount << endl;
		cout << "IO Write Count " << pcbs.getPCB(i)->stats.ioWriteCount << endl;
		cout << "Page Faults: " << pcbs.getPCB(i)->stats.pageFaults << endl;
		cout << "CPU ID: " << pcbs.getPCB(i)->cpuID << endl << endl;
	}
	//int test;
	//std::cin >> test;

	return 0;
}

