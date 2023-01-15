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
		image* img;


		virtual void place();
		inline void placeExtra();
		inline void destroyExtra();
		virtual void AddImageExtra();
		virtual void SendImage();

		HANDLE winmade = CreateEvent(NULL, FALSE, FALSE, NULL);

	public:


		//constructors
		ChildWindow();
		ChildWindow(const wstring& Text, int x, int y, int width, int height, MainWindow* parent);
		ChildWindow(wstring&& Text, int x, int y, int width, int height, MainWindow* parent);

		//manipulation
		virtual void Addimage(image& name);
		void AddBorder();
		void RemoveBorder();
		void resize(int width, int height);
		void Move(int DX, int DY);
		void Reposition(int x, int y);
		//setup (not fron constructor)
		void set(const wstring& Text, int x, int y, int width, int height, MainWindow* parent);
		void set(wstring&& Text, int x, int y, int width, int height, MainWindow* parent);
		const wstring& GetText() const;
		void E_Destroy();








		//void set(wstring&& Text, int x, int y, int width, int height, ExtraWindow* parent);

		void Remove();


	};

}