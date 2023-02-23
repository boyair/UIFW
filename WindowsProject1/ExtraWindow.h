#pragma once
#include"MainWindow.h"
#include <thread>

namespace UIFW {
	class ExtraWindow :public MainWindow
	{
		friend void HandleOnThread(ExtraWindow& window);
		friend class ChildWindow;

	public:
		HANDLE winmade; //handle to event which is et when window was made
		std::thread procthread; //the thread on which the message loop run
		ExtraWindow();
		ExtraWindow(const wstring& Text, int x, int y, int width, int height, unsigned char R, unsigned  char G, unsigned  char B);
		ExtraWindow(wstring&& Text, int x, int y, int width, int height, unsigned char R, unsigned  char G, unsigned  char B);
		ExtraWindow(wstring&& Text, int x, int y, int width, int height, const image& img);
		ExtraWindow(const wstring& Text, int x, int y, int width, int height, const image& img);
		void Init(const wstring& Text, int x, int y, int width, int height, unsigned char R, unsigned  char G, unsigned  char B);
		void Init(wstring&& Text, int x, int y, int width, int height, unsigned char R, unsigned  char G, unsigned  char B);
		void Destroy() override;
		~ExtraWindow();

	};
}
