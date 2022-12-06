#include "image.h"

image::image():BM(NULL), width(0), height(0)
{
}

bool image::ConatainsImage()
{
	return BM;
}

bool image::LoadFromFile(wstring&& name)
{
	this->name = name;
	name += (wstring)L".bmp";
	 BM = (HBITMAP)LoadImageW(NULL, name.c_str(), IMAGE_BITMAP, 0,0 , LR_LOADFROMFILE);
	 if (!BM)return false;
	 BITMAP temp;
	 GetObject(BM, sizeof(BITMAP),&temp);
	 width = temp.bmWidth;
	 height = temp.bmHeight;
	return true;
}
