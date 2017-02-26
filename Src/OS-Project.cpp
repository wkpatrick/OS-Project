// OS-Project.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CPU.h"
#include "Memory.h"
#include "PCB.h"
#include "LongTermScheduler.h"
#include <iostream>
#include <queue>
typedef unsigned long int WORD;
typedef unsigned char BYTE;

using namespace std;

int main()
{
	Memory disk = Memory(2048);
	Memory ram = Memory(1024);
	PCBList pcbs = PCBList();
	//queue stores id of PCB
	queue<int> readyQ;

	LongTermScheduler LTScheduler = LongTermScheduler(&ram, &disk, &pcbs, &readyQ);

	ram.addWord(0xFFFFFFFF); //You can assign data this way
	ram.setWord(0x0000001,32); //You can address ram in hex as well, and assign decimals, it all works.

	cout << ram.getWord(1) << endl;

	int test;
	std::cout << "Hello world!" << std::endl;
	WORD testByte = 0b10100000000000000000000000000000;   //How you define a number in binary;
	WORD testWord = 0xFFFFFFFF;

	WORD first2Bits = 0b11000000000000000000000000000000;
	
	unsigned char testBorks = 0b11111111;
	unsigned char twoBork = 0b11110000;

	unsigned char result = (testBorks & twoBork) >> 4;
	WORD testResult = (testWord & first2Bits) >> 30;


	cout << "First 2 bits " << result << endl;






	std::cin >> test;
    return 0;
}

