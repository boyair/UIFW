#pragma once
#define BufferSize 16
#include<string>


class wstring
{
	union
	{
		size_t size;
		wchar_t SmallBuffer[BufferSize];
	};
	wchar_t* str;
public:

	//constructors

	wstring();
	wstring(const wchar_t* str);
	wstring(const wstring& other);
	wstring(wstring&& other) noexcept;

	//reassing operations

	void operator =(const wstring& other);
	void operator = (const wchar_t* str);
	wstring& operator = (wstring&& other)noexcept;
	//indexing

	wchar_t& operator[](size_t index);
	//access char*

	wchar_t* c_str()const;


	size_t getlength()const;
	unsigned int getsize()const;
	void resize(unsigned int newsize);

	~wstring();



};

