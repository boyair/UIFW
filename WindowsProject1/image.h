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
	bool LoadFromFile(const wstring& name, int width, int height);
	bool LoadFromFile(wstring&& name);
	bool LoadFromFile(const wstring& name);
	image(wstring&& name);
	image(const wstring& name);
	image();
	~image();
	bool ConatainsImage();
	

};

