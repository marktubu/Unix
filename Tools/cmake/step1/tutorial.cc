#include <iostream>
#include <string>

#include "TutorialConfig.h"

using namespace std;

int main(int argc, char* argv[])
{
	std::cout << argv[0] << " Version " << Tutorial_VERSION_MAJOR << "." << Tutorial_VERSION_MINOR << std::endl;
	const double inputValue = std::stod(argv[1]);
	std::cout << "input number: " << inputValue << std::endl;
	return 0;
}
