#pragma once
#include <Windows.h>
#include "wstring.h"

class image
{
	friend class ChildWindow;
	friend class Button;
	friend class ExtraWindow;
	HBITMAP BM;
	wstring name;
	int width, height;

public:
	bool LoadFromFile(wstring&& name,int width,int height);
	bool LoadFromFile(wstring&& name);
	image();
	bool ConatainsImage();
	

};

