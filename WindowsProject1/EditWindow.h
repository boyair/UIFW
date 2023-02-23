#pragma once
#include "ChildWindow.h"
#include<math.h>
#define Hscroll 0x0080L
#define Vscroll 0x0044L
namespace UIFW {
	class EditWindow :public ChildWindow
	{
		// basic functions used in a lot of style change functions.
		void place() override;
		void UpdateText();
		static long EditWindowBKCLR, EditWindowTXCLR;

	public:

		//creators
		EditWindow();
		EditWindow(const wstring& Text, int x, int y, int width, int height, MainWindow* parent);
		EditWindow(wstring&& Text, int x, int y, int width, int height, MainWindow* parent);
		EditWindow(EditWindow&) = delete;

		//basic functionallity
		wstring GetText();
		//style change

		void AddVerticalScrolling();
		void AddHorizontalScrolling();
		void RemoveVerticalScrolling();
		void RemoveHorizontalScrolling();
		void SetStyle(unsigned long NewStyle) override;



		~EditWindow();
	};
}