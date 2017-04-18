#pragma once
#include "Page.h"
typedef unsigned long int WORD;

class Frame
{
public:
	Frame();
	~Frame();

	Page loadedPage;
	int pageNumber;
	bool isLoaded;

};

