#include "Menu.h"

HMENU Menu::hmenu = CreateMenu();
Menu::Menu(const wstring& name, long id, bool parent) : name(name), id(id), parent(parent), child(0)
{
	

	if (parent)
	{
		child = CreateMenu();
		AppendMenu(hmenu, MF_POPUP, (UINT_PTR)child, name.c_str());
	}
	else
	AppendMenu(hmenu, MF_STRING, id, name.c_str());

	
	

}
bool Menu::AddSubMenu(const wstring& name, long id)
{
	if (!parent) return false;
	
	AppendMenu(child, MF_STRING , id, name.c_str());
	return true;

}

void Menu::destroy()
{
	//SetMenu(parentWindow,NULL);
}
