#pragma once
#include<Windows.h>
#include "image.h"
#include "wstring.h"
#include "ExtraWindow.h"

#define Border 0x00800000L

class ChildWindow:public Window
{

protected:
	MainWindow* parent;

	
	
	virtual void place();
	virtual void placeExtra();

public:
	
	
	ChildWindow(); 
	
	ChildWindow(const wstring& Text, int x, int y, int width, int height, MainWindow* parent);
	ChildWindow( wstring&& Text, int x, int y, int width, int height, MainWindow* parent);

	void SetText(const wstring& Text);
	void SetText(wstring&& Text);

	
	  void SetColorText(int R, int G, int B);

	virtual void addimage(const image& name) ;
	virtual void AddBorder();
	virtual void RemoveBorder();
	virtual void resize(int width, int height);
	virtual void Move(int DX, int DY);
	virtual void Reposition(int x,int y);
	const wstring& GetText() const;
	void set(const wstring& Text, int x, int y, int width, int height, MainWindow* parent);
	void set(wstring&& Text, int x, int y, int width, int height, MainWindow* parent);
	void set(const wstring& Text, int x, int y, int width, int height, ExtraWindow* parent);
	void set(wstring&& Text, int x, int y, int width, int height, ExtraWindow* parent);
	 
	void Remove();


};

