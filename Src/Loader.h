#pragma once
#include "Memory.h"

class Loader
{
public:
	Loader(Memory *_disk, PCBList *list);
	~Loader();
	void load_file();

private:
	PCBList *list;
	Memory *disk;
};