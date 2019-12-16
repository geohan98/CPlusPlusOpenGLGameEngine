#pragma once
#include "systems/renderer/renderCommand.h"
#include "glad/glad.h"


namespace Engine
{
	class OpenGL_ClearDepthColourBufferCommand : public RenderCommand
	{
	public:
		void action() override;
	};

	void OpenGL_ClearDepthColourBufferCommand::action()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	class OpenGL_setClearColourCommand : public RenderCommand
	{
	private:
		float m_r, m_g, m_b, m_a;
	public:
		OpenGL_setClearColourCommand(float r, float g, float b, float a) : m_r(r), m_g(g), m_b(b), m_a(a) {};
		void action() override;
	};

	void OpenGL_setClearColourCommand::action()
	{
		glClearColor(m_r, m_g, m_b, m_a);
	}

	class OpenGL_setDepthTestLessCommand : public RenderCommand
	{
	private:
		bool m_enabled;
	public:
		OpenGL_setDepthTestLessCommand(bool enabled) : m_enabled(enabled) {};
		void action() override;
	};

	void OpenGL_setDepthTestLessCommand::action()
	{
		if (m_enabled)
		{
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LESS);
		}
		else
		{
			glDisable(GL_DEPTH_TEST);
		}
	}

	class OpenGL_setBackFaceCullingCommand : public RenderCommand
	{
	private:
		bool m_enabled;
	public:
		OpenGL_setBackFaceCullingCommand(bool enabled) : m_enabled(enabled) {};
		void action() override;
	};

	void OpenGL_setBackFaceCullingCommand::action()
	{
		if (m_enabled)
		{
			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);
		}
		else
		{
			glDisable(GL_CULL_FACE);
		}
	}
}