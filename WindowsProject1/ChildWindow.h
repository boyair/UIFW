#pragma once
#include<Windows.h>
#include<string>

class ChildWindow
{
protected:
	HWND Box;
	HWND parent;

	wchar_t* text;
	unsigned int textlength;

	
	int x, y, width, height;
	unsigned long style;
	ChildWindow(); 
	ChildWindow(const wchar_t* Text, int x, int y, int width, int height, HWND* parent);
	virtual void place() = 0;


public:


	void SetText(const wchar_t* Text);
	 virtual void Move(int DX, int DY);
	 virtual void resize(int width, int height);
	 virtual void AddBorder();
	 virtual void RemoveBorder();
	 
	 void Remove();



};

