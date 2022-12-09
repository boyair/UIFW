#pragma once
#include <Windows.h>
#include "wstring.h"
class ChildWindow;
class Button;
class image
{
	friend class ChildWindow;
	friend class Button;

	HBITMAP BM;
	wstring name;
	int width, height;

public:
	bool LoadFromFile(wstring&& name,int width,int height);
	bool LoadFromFile(wstring&& name);
	image();
	bool ConatainsImage();
	

};

