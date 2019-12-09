#include "engine_pch.h"
#include "include/platform/OpenGL/OpenGL_shader.h"
#include "systems/renderer/bufferLayout.h"
#include "glad/glad.h"
#include "systems/log.h"

#include <iostream>
#include <fstream>

namespace Engine
{
	void OpenGL_Shader::parseShader(const std::string& filepath)
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
			if (line.find("in") != std::string::npos)
			{

			}
			// Check if line contains 'in'
			// if it does, find the next word after 'in'
			// Convert to data type
			// Add to buffer layout

			if (region != NONE) src[region] += (line + "\n");
		}

		handle.close();

		compileAndLink(src[VERTEX], src[FRAGMENT]);
	}

	void OpenGL_Shader::compileAndLink(std::string & vertex, std::string & fragment)
	{
		unsigned int vs, fs;
		bool success;

		success = compile(GL_VERTEX_SHADER, vertex, vs);
		if (success == GL_FALSE) { return; }

		success = compile(GL_FRAGMENT_SHADER, fragment, fs);
		if (success == GL_FALSE) {
			glDeleteShader(vs);
			return;
		}

		unsigned int program = glCreateProgram();

		glAttachShader(program, vs);
		glAttachShader(program, fs);
		glLinkProgram(program);
		//glValidateProgram(program);

		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
			LOG_CORE_ERROR("Shader linking error: {0}", std::string(infoLog.begin(), infoLog.end()));

			glDeleteProgram(program);
			glDeleteShader(vs);
			glDeleteShader(fs);

			return;
		}

		glDetachShader(program, vs);
		glDetachShader(program, fs);

		//glDeleteShader(vs);
		//glDeleteShader(fs);

		program_ID = program;
	}

	bool OpenGL_Shader::compile(unsigned int type, const std::string& source, unsigned int & id)
	{
		id = glCreateShader(type);
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
			LOG_CORE_ERROR("Failed To Compile {0} shader! '{1}'", (type == GL_VERTEX_SHADER ? "Vertex" : "fragment"), msg);
			glDeleteShader(id);
		}

		return result;
	}

	int OpenGL_Shader::getUniformLocation(const std::string name)
	{

	}

	OpenGL_Shader::OpenGL_Shader(const std::string& filepath)
	{


	}

	OpenGL_Shader::OpenGL_Shader(const std::string& vertexFilePath, const std::string& fragmentFilePath)
	{

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