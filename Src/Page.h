#pragma once
typedef unsigned long int WORD;
class Page
{
public:
	Page();
	~Page();

	int pageNumber;
	WORD contents[4]; 
	
};

