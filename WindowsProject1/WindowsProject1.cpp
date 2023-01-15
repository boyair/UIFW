#include <sstream>
#include "UIFW.h"
using namespace UIFW;
image img2(L"tank",90,90);
image img(L"B.bmp");
MainWindow win(L"W working window1", 500, 20, 1000, 1000, img);
ExtraWindow win2(L"W working window2", 1000, 20, 1000, 1000,90,245,78);
ExtraWindow win3(L"W working window3", 2000, 20, 1000, 1000,200,45,23);
Button nums2[10] = { (0),(1),(2),(3),(4),(5),(6),(7),(8),(9) };
Button nums[10] = {(0),(1),(2),(3),(4),(5),(6),(7),(8),(9)};
ChildWindow edit;
EW editest(L"test", 500, 500, 100, 100, &win);
 




void(*buttons[])() = { 
	[]() {edit.SetText(edit.GetText() + L"0");
POINT p = win2.GetMousePos();

std::wstringstream ss;
ss << p.x << L"  " << p.y;
nums[0].SetText(ss.str().c_str());

},
	[]() {edit.SetText(edit.GetText() + L"1"); 
win.RemoveMenuBar(); },

[]() {edit.SetText(edit.GetText() + L"2"); 
edit.SetText(L"LOLOLO");
nums[6].Addimage(img2);
editest.AddVerticalScrolling();
},

[]() {edit.SetText(edit.GetText() + L"3");
win2.RemoveMenuBar(); 
UpdateWindow(win3.Hwnd);
editest.RemoveVerticalScrolling();
},
[]() {

edit.SetText(edit.GetText() + L"4");
//edit.AddBorder();
edit.set(0, 500, 700, 500, 100, &win);
edit.Reposition(900, 900);
}
,[]() {edit.SetText(edit.GetText() + L"5"); 
},[]() {edit.SetText(edit.GetText() + L"6"); },
[]() {edit.SetText(edit.GetText() + L"7");  },[]() {edit.SetText(edit.GetText() + L"8"); },[]() {edit.SetText(edit.GetText() + L"9"); },


};
int main()
{
	//win2.AddMenu(L"long menu name what will happen??", 6, false);
	for (int i = 0; i < 10; i++)
	{
		std::wstringstream wss;
		wss << i;

		nums2[i].set(wss.str().c_str(), ((i % 3) + 1) * 90, i / 3 * 90 + 90, 30, 30, &win2);
		
		win2.AddFunc(i, buttons[i]);
		wss.clear();
	}
	//nums2[6].Addimage(img2);

for (int i = 0; i < 10; i++)
	{
		std::wstringstream wss;
		wss << i;

		nums[i].set(wss.str().c_str(), ((i % 3) + 1) * 90, i / 3 * 90 + 90, 90, 90, &win);
		win.AddFunc(i, buttons[i]);
		wss.clear();
	}

//edit.set(0, 500, 500, 500, 100, &win);

	win.start();
	


	

}

int WINAPI WinMain(_In_ HINSTANCE hInstance,_In_opt_ HINSTANCE hPrevInstance,_In_ LPSTR lpCmdLine,_In_ int nShowCmd)
{

	main();
	
}
