#include "image.h"

bool image::LoadFromFile(wstring&& name, int width, int height)
{
	this->name = std::move(name);
	if (this->name[this->name.getlength() - 4] != L'.')
		this->name += (wstring)L".bmp";
	BM = (HBITMAP)LoadImageW(NULL, this->name.c_str(), IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	if (!BM)return false;
	this->width = width;
	this->height = height;
	return true;
}

image::image():BM(NULL), width(0), height(0)
{
}

image::image(wstring&& name) :BM(NULL), width(0), height(0)
{
	LoadFromFile(std::move(name));

}

image::~image()
{
	if(BM) DeleteObject(BM);

}

bool image::ConatainsImage()
{
	return BM;
}

bool image::LoadFromFile(wstring&& name)
{
	this->name = std::move(name);
	if(this->name[this->name.getlength()-4]!=L'.')
		this->name += (wstring)L".bmp";
	 BM = (HBITMAP)LoadImageW(NULL, this->name.c_str(), IMAGE_BITMAP, 200,200 , LR_CREATEDIBSECTION |LR_LOADFROMFILE);
	 if (!BM)return false;
	 BITMAP temp;
	 GetObject(BM, sizeof(BITMAP),&temp);
	 width = temp.bmWidth;
	 height = temp.bmHeight;
	return true;
}
