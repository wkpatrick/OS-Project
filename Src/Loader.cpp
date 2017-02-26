#pragma once
#include "PCB.h"
#include "Loader.h"

#include "stdafx.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

/*
Created by: Andrew Kartawinata

Currently does not place attributes or instructions anywhere
Currently is able to extract necessary info from program file
*/
using namespace std;

Loader::Loader(void)
{
}

Loader::~Loader(void)
{
}

void Loader::load_file()
{
	string line; //String object used to hold read objects
	ifstream testprogram; //Object variable for holding a file to be read

	int Job_ID, Word_Count, Priority; //Job ID, #of words in job, priority number
	int in_buf_sz, out_buf_sz, tmp_buf_sz; //Input buffer size, output buffer size, temp. buffer size
	int disk_line_counter = 0;
	static int empty_line_count = 0;
	static int frame_adjusted_code_size = 0;

	testprogram.open("Program-File.txt");

	if (testprogram.is_open())
	{
		while (getline(testprogram, line))
		{
			if (line.substr(0, 6) == "// JOB") //Extracts Job attributes
			{
				sscanf_s(line.c_str(), "%*s%*s%x%x%x", &Job_ID, &Word_Count, &Priority);

				frame_adjusted_code_size = 4 * (int)((Word_Count / 4.0) + 0.5);
				empty_line_count = frame_adjusted_code_size - Word_Count;
			}
			else if (line.substr(0, 8) == "// Data ") //Extracts Data attributes
			{
				sscanf_s(line.c_str(), "%*s%*s%x%x%x", &in_buf_sz, &out_buf_sz, &tmp_buf_sz);

				disk_line_counter += empty_line_count;
			}
			else if (line.substr(0, 2) == "0x") //Extracts instructions
			{
				char test_line[9];
				for (int i = 0; i < 8; i++)
				{
					test_line[i] = line[2 + i];
				}
				test_line[8] = NULL;
				disk_line_counter++;
			}
			else if ((line.substr(0, 6) == "// END") || (line.substr(0, 5) == "//END"))
			{
				cout << "line cnt this section:  " << disk_line_counter << endl;
			}

		}
		testprogram.close();
	}
	else
		cout << "Cannot open file" << "\n";
}
