#pragma once
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include<iostream>


class IniParser
{
private:
	std::map<std::string, std::string> m_data;
public:
	IniParser(const char* _filepath)
	{
		std::fstream file(_filepath, std::ios::in);
		std::string line;
		while (getline(file, line))
		{
			if (line.find("=") != std::string::npos)
			{
				std::string name, data;
				line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
				name = line.substr(0, line.find("="));
				data = line.substr(line.find("=") + 1);
				m_data[name] = data;
			}
		}
	}

	int getDataInt(std::string _name)
	{
		int i = -1;
		try
		{
			i = std::stoi(m_data[_name]);
		}
		catch (const std::invalid_argument&)
		{
			std::cout << "BAD INPUT!" << std::endl;
		}
		catch (const std::out_of_range&)
		{
			std::cout << "OUT OF RANGE!" << std::endl;
		}
		return i;
	}

	float getDataFloat(std::string _name)
	{
		float f = -1;
		try
		{
			f = std::stof(m_data[_name]);
		}
		catch (const std::invalid_argument&)
		{
			std::cout << "BAD INPUT!" << std::endl;
		}
		catch (const std::out_of_range&)
		{
			std::cout << "OUT OF RANGE!" << std::endl;
		}
		return f;
	}
};