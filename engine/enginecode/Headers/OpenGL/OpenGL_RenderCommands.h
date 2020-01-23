#pragma once
#include "../enginecode/Headers/renderer/renderCommand.h"
#include <glad/glad.h>


namespace Engine
{
	namespace Renderer {
		/**
		 * Asset Manager, template class for handling a single type
		 */
		class OpenGL_ClearDepthColourBufferCommand : public RenderCommand
		{
		public:
			OpenGL_ClearDepthColourBufferCommand(bool destroy) { dontDestroyOnAction = destroy; };
			void action() override; ///< Action the command
		};

		void OpenGL_ClearDepthColourBufferCommand::action()
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		/**
		 * Asset Manager, template class for handling a single type
		 */
		class OpenGL_setClearColourCommand : public RenderCommand
		{
		private:
			float m_r, m_g, m_b, m_a; ///< Clear color
		public:
			OpenGL_setClearColourCommand(float r, float g, float b, float a, bool destroy) : m_r(r), m_g(g), m_b(b), m_a(a) { dontDestroyOnAction = destroy; };
			void action() override;///< Action the command
		};

		void OpenGL_setClearColourCommand::action()
		{
			glClearColor(m_r, m_g, m_b, m_a);
		}

		/**
		 * Asset Manager, template class for handling a single type
		 */
		class OpenGL_setDepthTestLessCommand : public RenderCommand
		{
		private:
			bool m_enabled; ///< Should it be enabled
		public:
			OpenGL_setDepthTestLessCommand(bool enabled, bool destroy) : m_enabled(enabled) { dontDestroyOnAction = destroy; };
			void action() override;///< Action the command
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

		/**
		 * Asset Manager, template class for handling a single type
		 */
		class OpenGL_setBackFaceCullingCommand : public RenderCommand
		{
		private:
			bool m_enabled; ///< Should it be enabled
		public:
			OpenGL_setBackFaceCullingCommand(bool enabled, bool destroy) : m_enabled(enabled) { dontDestroyOnAction = destroy; };
			void action() override;///< Action the command
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

		/**
		 * Asset Manager, template class for handling a single type
		 */
		class OpenGL_setPolygonModeFill : public RenderCommand
		{
		public:
			OpenGL_setPolygonModeFill(bool destroy) { dontDestroyOnAction = destroy; };
			void action() override;///< Action the command
		};

		void OpenGL_setPolygonModeFill::action()
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}

		/**
		 * Asset Manager, template class for handling a single type
		 */
		class OpenGL_setPolygonModeLine : public RenderCommand
		{
		public:
			OpenGL_setPolygonModeLine(bool destroy) { dontDestroyOnAction = destroy; };
			void action() override;///< Action the command
		};

		void OpenGL_setPolygonModeLine::action()
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}

		/**
		 * Asset Manager, template class for handling a single type
		 */
		class OpenGL_setPolygonModePoint : public RenderCommand
		{
		public:
			OpenGL_setPolygonModePoint(bool destroy) { dontDestroyOnAction = destroy; };
			void action() override;///< Action the command
		};

		void OpenGL_setPolygonModePoint::action()
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		}

		/**
		 * Asset Manager, template class for handling a single type
		 */
		class OpenGL_setBlendMode : public RenderCommand
		{
		private:
			bool m_enabled; ///< Should it be enabled
		public:
			OpenGL_setBlendMode(bool enabled, bool destroy) : m_enabled(enabled) { dontDestroyOnAction = destroy; };
			void action() override;///< Action the command
		};

		void OpenGL_setBlendMode::action()
		{
			if (m_enabled)
			{
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			}
			else
			{
				glEnable(GL_BLEND);
			}
		}

	}
}