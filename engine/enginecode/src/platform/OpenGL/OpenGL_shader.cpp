#include "engine_pch.h"
#include "include/platform/OpenGL/OpenGL_shader.h"
#include "systems/renderer/bufferLayout.h"
#include "glad/glad.h"

#include <iostream>
#include <fstream>

namespace Engine
{
	std::string OpenGL_Shader::parseShader(const std::string& filepath)
	{
		std::ifstream stream(filepath);
		std::string content;
		content.assign((std::istreambuf_iterator<char>(stream)), (std::istreambuf_iterator<char>()));
		return content;
	}

	unsigned int OpenGL_Shader::compileShader(unsigned int type, const std::string source)
	{
		unsigned int id = glCreateShader(type);
		const char* src = source.c_str();
		glShaderSource(id, 1, &src, nullptr);
		glCompileShader(id);

		int result;
		glGetShaderiv(id, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)
		{
			int length;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
			char* msg = (char*)_malloca(length * sizeof(char));
			glGetShaderInfoLog(id, length, &length, msg);
			std::cout << "Failed To Compile " << (type == GL_VERTEX_SHADER ? "Vertex" : "fragment") << " shader!" << std::endl;
			std::cout << msg << std::endl;
			glDeleteShader(id);
			return 0;
		}

		return id;
	}

	int OpenGL_Shader::getUniformLocation(const std::string name)
	{

	}

	OpenGL_Shader::OpenGL_Shader(const std::string& filepath)
	{


	}

	OpenGL_Shader::OpenGL_Shader(const std::string& vertexFilePath, const std::string& fragmentFilePath)
	{
		program_ID = glCreateProgram();
		unsigned int vs = compileShader(GL_VERTEX_SHADER, parseShader(vertexFilePath));
		unsigned int fs = compileShader(GL_FRAGMENT_SHADER, parseShader(fragmentFilePath));

		glAttachShader(program_ID, vs);
		glAttachShader(program_ID, fs);
		glLinkProgram(program_ID);
		glValidateProgram(program_ID);

		glDeleteShader(vs);
		glDeleteShader(fs);
	}

	unsigned int OpenGL_Shader::id()
	{
		return program_ID;
	}

	void OpenGL_Shader::bind()
	{
		glUseProgram(program_ID);
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

	BufferLayout Engine::OpenGL_Shader::getBufferLayout() const
	{
		return BufferLayout();
	}

	UniformLayout Engine::OpenGL_Shader::getUniformLayout() const
	{
		return UniformLayout();
	}
}