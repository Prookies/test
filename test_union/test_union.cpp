#include <iostream>

union UnionTest{
	UnionTest() : i(10){};
	int i;
	double d;
};

int main()
{
	UnionTest u;

	std::cout << u.i << std::endl;

	std::cout << sizeof(u) << std::endl;
}