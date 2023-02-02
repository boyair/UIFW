#pragma once
#include "ChildWindow.h"
namespace UIFW {
	class Button : public ChildWindow
	{
		long long id;
		void place() override;

	public:
		Button(Button&) = delete;

		Button(long long id);
		Button(const wstring& Text, int x, int y, int width, int height, long long id, MainWindow* parent);
		Button(wstring&& Text, int x, int y, int width, int height, long long id, MainWindow* parent);
		void SetID(long long id);
		void Addimage(image& img) override;
		~Button();


	};

}