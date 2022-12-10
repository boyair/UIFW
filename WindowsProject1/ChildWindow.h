#pragma once
#include<Windows.h>
#include "image.h"
#include "wstring.h"


#define Border 0x00800000L

class ChildWindow
{

protected:
	HWND parent;

	wstring text;
	
	int x, y, width, height;
	unsigned long style;
	virtual void place();

public:
	
	HWND Box;
	ChildWindow(); 
	
	ChildWindow(const wstring& Text, int x, int y, int width, int height, HWND* parent);
	ChildWindow( wstring&& Text, int x, int y, int width, int height, HWND* parent);

	void SetText(const wstring& Text);
	void SetText(wstring&& Text);

	
	 static void SetTextColor(int R, int G, int B);

	virtual void addimage(const image& name) ;
	virtual void AddBorder();
	virtual void RemoveBorder();
	virtual void resize(int width, int height);
	virtual void Move(int DX, int DY);
	virtual void Reposition(int x,int y);
	void set(const wstring& Text, int x, int y, int width, int height, HWND* parent);
	void set(wstring&& Text, int x, int y, int width, int height, HWND* parent);
	 
	void Remove();


};

