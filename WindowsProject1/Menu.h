#pragma once
#include <Windows.h>
#include <vector>
#include <string>
class Menu
{
	HWND& parentWindow;
	 std::string name;
	const bool parent;
	HMENU child;
	static HMENU hmenu;
	 const long id;
public:
	Menu(HWND* parentWindow, const std::string& name, long id, bool parent);
	bool AddSubMenu(const std::string& name, long id);
	static void destroy();


};

