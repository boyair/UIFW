#pragma once
#include<Windows.h>
#include "image.h"
#include "wstring.h"
#include "ExtraWindow.h"

#define Border 0x00800000L
namespace UIFW {
	class ChildWindow :public Window
	{
		friend class MainWindow;
		friend class ExtraWindow;
	protected:
		MainWindow* parent;
		virtual void place(); // runs the command needed to create a window
		void PlaceExtra();	//sends a message to parent window to run place() on its thread.
		void DestroyExtra(); //sends a message to parent window to run Destroy() on its thread.

		HANDLE winmade = CreateEvent(NULL, FALSE, FALSE, NULL);

	public:

		//constructors
		ChildWindow();
		ChildWindow(ChildWindow&) = delete;
		ChildWindow(const wstring& Text, int x, int y, int width, int height, MainWindow* parent);
		ChildWindow(wstring&& Text, int x, int y, int width, int height, MainWindow* parent);
		//manipulation
		virtual void Addimage(image& name);
		void AddBorder();
		void RemoveBorder();
		//setup (not from constructor)
		void Init(const wstring& Text, int x, int y, int width, int height, MainWindow* parent);
		virtual void SetStyle(unsigned long NewStyle);
		void Init(wstring&& Text, int x, int y, int width, int height, MainWindow* parent);
		void Destroy();
		
	


	};

}