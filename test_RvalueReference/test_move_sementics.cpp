#include <iostream>
#include <vector>
#include <string.h>
#include <stdlib.h>

using std::cin;
using std::cout;
using std::endl;

class MyString
{
private:
	char *_data;
	size_t _len;
	void _init_data(const char *s)
	{
		_data = new char[_len + 1];
		memcpy(_data, s, _len);
		_data[_len] = '\0';
	}

public:
	MyString()
	{
		_data = NULL;
		_len = 0;
	}

	MyString(const char *p)
	{
		_len = strlen(p);
		_init_data(p);
	}

	MyString(const MyString &str)
	{
		_len = str._len;
		_init_data(str._data);
		std::cout << "Copy Constructor is called! source: " << str._data << std::endl;
	}

	MyString &operator=(const MyString &str)
	{
		if (this != &str)
		{
			_len = str._len;
			_init_data(str._data);
		}
		std::cout << "Copy Assignment is called! source: " << str._data << std::endl;
		return *this;
	}

	MyString(MyString &&str)
	{
		std::cout << "Move Constructor is called! source: " << str._data << std::endl;
		_len = str._len;
		_data = str._data;
		str._len = 0;
		str._data = NULL; // ! 防止在析构函数中将内存释放掉
	}

	MyString &operator=(MyString &&str)
	{
		std::cout << "Move Assignment is called! source: " << str._data << std::endl;
		if (this != &str)
		{
			_len = str._len;
			_data = str._data;
			str._len = 0;
			str._data = NULL; // ! 防止在析构函数中将内存释放掉
		}
		return *this;
	}

	friend std::ostream &operator<<(std::ostream &os, const MyString &str);

	virtual ~MyString()
	{
		if (_data != NULL)
		{
			std::cout << "Destructor is called! " << std::endl;
			free(_data);
		}
	}
};

std::ostream &operator<<(std::ostream &os, const MyString &str)
{
	os << str._data;
}

void test1()
{
	MyString a;
	a = MyString("Hello");
	std::vector<MyString> vec;
	vec.push_back(MyString("World"));
}

void ProcessValue(MyString &i)
{
	std::cout << "LValue processed: " << i << endl;
}

void ProcessValue(MyString &&i)
{
	std::cout << "RValue processed: " << i << endl;
}

void test2()
{
	MyString a("str");
	ProcessValue(a);
	ProcessValue(std::move(a));

	cout << "a = " << a << endl;
}

template <class T>
void swap1(T &a, T &b)
{
	T tmp(a); // copy a to tmp
	a = b;	  // copy b to a
	b = tmp;  // copy tmp to b
}

template <class T>
void swap2(T &a, T &b)
{
	T tmp(std::move(a)); // move a to tmp
	a = std::move(b);	 // move b to a
	b = std::move(tmp);	 // move tmp to b
}

void test3()
{
	MyString a("a");
	MyString b("b");

	swap1(a, b);
	cout << a << " : " << b << endl;
	swap2(a, b);
	cout << a << " : " << b << endl;
}

int main()
{
	std::string str(20, '*');
	test1();
	cout << str << endl;
	test2();
	cout << str << endl;
	test3();
}
