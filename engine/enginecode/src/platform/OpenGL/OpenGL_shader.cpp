#include "engine_pch.h"
#include "systems/log.h"
#include "include/platform/OpenGL/OpenGL_shader.h"
#include "systems/renderer/bufferLayout.h"
#include "glad/glad.h"

#include <iostream>
#include <fstream>

namespace Engine
{
	void OpenGL_Shader::parseSource(const std::string& filepath)
	{
		std::fstream handle(filepath, std::ios::in);
		enum { NONE = -1, VERTEX = 0, FRAGMENT } region;
		if (!handle.is_open()) LOG_CORE_CRITICAL("COULD NOT OPEN SHADER FILE '{0}'", filepath);

		std::string line, src[2];

		while (getline(handle, line))
		{
			if (line.find("#region Vertex") != std::string::npos) { region = VERTEX; continue; }
			if (line.find("#region Fragment") != std::string::npos) { region = FRAGMENT; continue; }
			if (line.find("#region Geomatry") != std::string::npos) { region = NONE; continue; }
			if (line.find("#region Tessalation") != std::string::npos) { region = NONE; continue; }

			if (line.find(" in ") != std::string::npos)
			{
				std::string x = line;
				x = x.substr(x.find("in") + 3);
				x = x.erase(x.find(" "));
				//LOG_CORE_INFO(x);
				m_bufferlayout.addElement(GLSLStrToSDT(x));
			}

			if (line.find("uniform ") != std::string::npos)
			{
				std::string x = line;
				x = x.substr(x.find("uniform") + 8);
				std::string y = x;
				x = x.erase(x.find(" "));

				y = y.substr(x.size() + 1, y.find(";"));
				y = y.erase(y.find(";"));
				//LOG_CORE_INFO(x);
				//LOG_CORE_INFO(y);
				m_uniformLayout[y].first = (void*)GLSLStrToSDT(x);
				m_uniformLayout[y].second = -1;
			}


			if (region != NONE) src[region] += (line + "\n");
		}

		handle.close();

		compileAndLink(src[VERTEX], src[FRAGMENT]);
	}

	void OpenGL_Shader::compileAndLink(std::string& vertex, std::string& fragment)
	{
		//VERTEX SHADER
		unsigned int VS = glCreateShader(GL_VERTEX_SHADER);
		const char* src = vertex.c_str();
		glShaderSource(VS, 1, &src, 0);
		glCompileShader(VS);

		int result = 0;
		glGetShaderiv(VS, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)
		{
			int maxLength = 0;
			glGetShaderiv(VS, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(VS, maxLength, &maxLength, &infoLog[0]);
			LOG_CORE_ERROR("Shader compile error: {0}", std::string(infoLog.begin(), infoLog.end()));

			glDeleteShader(VS);
			return;
		}


		//FRAGMENT SHADER
		unsigned int FS = glCreateShader(GL_FRAGMENT_SHADER);
		src = fragment.c_str();
		glShaderSource(FS, 1, &src, 0);
		glCompileShader(FS);

		glGetShaderiv(FS, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)
		{
			int maxLength = 0;
			glGetShaderiv(FS, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(FS, maxLength, &maxLength, &infoLog[0]);
			LOG_CORE_ERROR("Shader compile error: {0}", std::string(infoLog.begin(), infoLog.end()));

			glDeleteShader(FS);
			glDeleteShader(VS);

			return;
		}

		//SHADER PROGRAM
		m_program_ID = glCreateProgram();
		glAttachShader(m_program_ID, VS);
		glAttachShader(m_program_ID, FS);
		glLinkProgram(m_program_ID);

		int isLinked = 0;
		glGetProgramiv(m_program_ID, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_program_ID, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(m_program_ID, maxLength, &maxLength, &infoLog[0]);
			LOG_CORE_ERROR("Shader linking error: {0}", std::string(infoLog.begin(), infoLog.end()));

			glDeleteProgram(m_program_ID);
			glDeleteShader(VS);
			glDeleteShader(FS);

			return;
		}

		glDetachShader(m_program_ID, VS);
		glDetachShader(m_program_ID, FS);

		setUniformLocations();
	}

	void OpenGL_Shader::setUniformLocations()
	{
		std::map<std::string, std::pair<void*, unsigned int>>::iterator it;

		for (auto it = m_uniformLayout.begin(); it != m_uniformLayout.end(); ++it)
		{
			if (it->second.second == -1)
			{
				it->second.second = glGetUniformLocation(m_program_ID, it->first.c_str());
				LOG_CORE_INFO("UNIFORM '{0}', LOCATION == '{1}'", it->first, it->second.second);
				if (it->second.second == -1)
				{
					LOG_CORE_ERROR("UNIFORM '{0}', DOES NOT EXSIST", it->first);
				}
			}
		}
	}

	OpenGL_Shader::OpenGL_Shader(const std::string& filepath) : m_program_ID(0)
	{
		parseSource(filepath);
	}

	OpenGL_Shader::OpenGL_Shader(const std::string& vertex, const std::string& fragment)
	{
	}

	unsigned int OpenGL_Shader::id()
	{
		return m_program_ID;
	}

	void OpenGL_Shader::bind()
	{
		glUseProgram(m_program_ID);
	}

	void OpenGL_Shader::unbind()
	{
		glUseProgram(0);
	}
	bool OpenGL_Shader::uploadData(const std::string& name, void* data)
	{
		return false;
	}
	bool OpenGL_Shader::uploadData(const UniformLayout& uniforms)
	{
		return false;
	}
	BufferLayout OpenGL_Shader::getBufferLayout() const
	{
		return m_bufferlayout;
	}
	UniformLayout OpenGL_Shader::getUniformLayout() const
	{
		return m_uniformLayout;
	}
}