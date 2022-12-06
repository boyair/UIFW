#pragma once
#include <Windows.h>
#include "wstring.h" 
class image
{
	HBITMAP BM;
	wstring name;
	int width, height;

public:

	image();

	bool ConatainsImage();
	bool LoadFromFile(wstring&& name);


};

