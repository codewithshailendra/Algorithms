#include<iostream>
#include "Sat.h"

const std::string s1{ R"(..\..\Data\sccTest.txt)" };
const std::string t1{ R"(..\..\Data\st1.txt)" };
const std::string t2{ R"(..\..\Data\st2.txt)" };
const std::string t3{ R"(..\..\Data\st3.txt)" };

void checkout() {
	char c;
	std::cout << "\nPress any key to exit\n";
	std::cin >> c;
}

int main()
{

	//////////////////////////////////////////
	//// This version was replaced by SCC ////
	//////////////////////////////////////////
	Sat G(s1, true);


	return 0;
}

