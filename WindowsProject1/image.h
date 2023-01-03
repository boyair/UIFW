#pragma once
#include <Windows.h>
#include "wstring.h"

class image
{
	friend class ChildWindow;
	friend class Button;
	friend class ExtraWindow;
	friend class MainWindow;
	HBITMAP BM;
	wstring name;
	int width, height;

public:
	bool LoadFromFile(wstring&& name,int width,int height);
	bool LoadFromFile(wstring&& name);
	image();
	image(wstring&& name);
	~image();
	bool ConatainsImage();
	

};

