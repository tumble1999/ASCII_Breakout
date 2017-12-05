#include <iostream>
#include <string>
# include "Hello.h"

template <typename T>
std::ostream& Print(T& s)
{
	return std::cout << s;
}

template <typename T>
std::ostream& PrintLn(T& s)
{
	return Print(s) << std::endl;
}

int main()
{
	std::cout << "Hello World!" << std::endl;
	std::string test = "hello";
	test += "face";

	PrintLn("Test");

	Test::N2::Hello hi;
	hi.Face();
	system("pause>null");
	return 0;
}