#pragma once
#include <map>
#include <string>
#include <fstream>
#include <algorithm>
#include<iostream>
#include "systems/log.h"

namespace Engine {

	class IniParser
	{
	private:
		std::map<std::string, std::string> m_data;
	public:
		IniParser(const char* _filepath)
		{
			std::fstream file(_filepath, std::ios::in);
			if (!file.is_open())
			{
				LOG_CORE_WARN("[INI PARSER][UNABLE TO OPEN FILE {0}]", _filepath);
			}
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

		int getDataInt(const char* _name)
		{
			if (m_data[_name].empty())
			{
				LOG_CORE_WARN("[INI PARSER][INT][VALUE EMPTY]");
				return -1;
			}

			int i = -1;
			try
			{
				i = std::stoi(m_data[_name]);
			}
			catch (const std::invalid_argument&)
			{
				LOG_CORE_WARN("[INI PARSER][INT][BAD INPUT]");

			}
			catch (const std::out_of_range&)
			{
				LOG_CORE_WARN("[INI PARSER][INT][OUT OF RANGE]");
			}
			return i;
		}

		float getDataFloat(const char* _name)
		{
			if (m_data[_name].empty())
			{
				LOG_CORE_WARN("[INI PARSER][FLOAT][VALUE EMPTY]");
				return -1;
			}

			float f = -1;
			try
			{
				f = std::stof(m_data[_name]);
			}
			catch (const std::invalid_argument&)
			{
				LOG_CORE_WARN("[INI PARSER][FLOAT][BAD INPUT]");
			}
			catch (const std::out_of_range&)
			{
				LOG_CORE_WARN("[INI PARSER][FLOAT][OUT OF RANGE]");
			}
			return f;
		}

		bool getDataBool(const char* _name)
		{
			if (m_data[_name].empty())
			{
				LOG_CORE_WARN("[INI PARSER][BOOL][VALUE EMPTY]");
				return -1;
			}

			if (m_data[_name] == "true" || m_data[_name] == "TRUE" || m_data[_name] == "1")
			{
				return true;
			}
			else if (m_data[_name] == "false" || m_data[_name] == "FALSE" || m_data[_name] == "0")
			{
				return false;
			}
			LOG_CORE_WARN("[INI PARSER][BOOL][DATA MISMATCH]");
			return false;
		}
	};
}