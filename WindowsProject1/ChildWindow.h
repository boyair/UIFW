#pragma once
#include<Windows.h>
#include<string>
#define Border 0x00800000L

class ChildWindow
{
protected:
	HWND parent;
	HWND Box;

	wchar_t* text;
	unsigned int textlength;

	
	int x, y, width, height;
	unsigned long style;
	virtual void place();

public:
	ChildWindow(); 
	ChildWindow(const wchar_t* Text, int x, int y, int width, int height, HWND* parent);


	void SetText(const wchar_t* Text);
	virtual void addimage(const wchar_t* name) ;
	 virtual void Move(int DX, int DY);
	 virtual void resize(int width, int height);
	 virtual void AddBorder();
	 virtual void RemoveBorder();
	 virtual void Reposition(int x,int y);
	 void set(const wchar_t* Text, int x, int y, int width, int height, HWND* parent);
	 
	 void Remove();



};

