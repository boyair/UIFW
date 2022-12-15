#pragma once
#include<string>

#define BufferSize 16
class wstring
{
	union
	{
		size_t size;
		wchar_t SmallBuffer[BufferSize] = {0};
	};
	wchar_t* str = SmallBuffer;
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

	const wchar_t* c_str()const;
	wchar_t* c_str();

	size_t getlength()const;
	size_t getsize()const;
	void resize(size_t newsize);
	void operator +=(const wstring& other);


	~wstring();



};

