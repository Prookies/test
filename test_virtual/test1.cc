#include <iostream>
using std::cout;
using std::endl;

class Base
{
public:
	virtual void show(){
		cout << "Base Show" << endl;
	}
	virtual ~Base(){
		show();
	}
};

class Derive : public Base
{
public:
	void show(){
		cout << "Derive Show" << endl;
	};
	virtual ~Derive(){
		show();
	};
};

int main()
{
	Base *p1 = new Base();
	delete p1;
	cout << "----------" << endl;
	Derive *p2 = new Derive();
	delete p2;
	cout << "----------" << endl;
	Base *p3 = new Derive();
	delete p3;
}
