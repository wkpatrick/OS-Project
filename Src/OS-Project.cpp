// OS-Project.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CPU.h"
#include <iostream>
typedef unsigned long int WORD;
typedef unsigned char BYTE;

int main()
{
	WORD Disk[2048];
	WORD Ram[1024];

	memset(Disk, 0, sizeof(Disk));
	memset(Ram, 0, sizeof(Ram));

	Ram[0] = 0xFFFFFFFF; //You can assign data this way
	Ram[0x0000001] = 32; //You can address ram in hex as well, and assign decimals, it all works.

	int test;
	std::cout << "Hello world!" << std::endl;
	std::cin >> test;
    return 0;
}

