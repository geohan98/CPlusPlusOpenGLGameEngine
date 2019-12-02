#include "engine_pch.h"
#include "include/platform/OpenGL/OpenGL_shader.h"
#include "systems/renderer/bufferLayout.h"
#include "glad/glad.h"

namespace Engine
{
	OpenGL_Shader::OpenGL_Shader()
	{
	}

	unsigned int OpenGL_Shader::id()
	{
		return 0;
	}

	void OpenGL_Shader::bind()
	{
		glUseProgram(program_ID);
	}

	void OpenGL_Shader::unbind()
	{
		glUseProgram(0);
	}

	bool OpenGL_Shader::uploadData(const std::string & name, void * data)
	{
		return false;
	}

	bool OpenGL_Shader::uploadData(const UniformLayout & uniforms)
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

	Shader * Engine::Shader::create(const std::string & filepath)
	{
		return nullptr;
	}

	Shader * Engine::Shader::create(const std::string & vertexFilePath, const std::string & fragmentFilePath)
	{
		return nullptr;
	}
}