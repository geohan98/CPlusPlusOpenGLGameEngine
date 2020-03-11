#include "iniParser.h"

int main()
{
	IniParser config = IniParser("config.ini");

	std::cout << config.getDataInt("width") << std::endl;
	std::cout << config.getDataFloat("mouseSensitivity") << std::endl;

	return 0;
}