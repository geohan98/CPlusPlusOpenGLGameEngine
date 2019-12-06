/** \file application.cpp
*/


#include "engine_pch.h"

#pragma region TempIncludes
// temp includes
#include <glad/glad.h>
#include <gl/GL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#pragma endregion TempIncludes

#include "core/application.h"
#ifdef NG_PLATFORM_WINDOWS
#include "include/platform/OpenGL/GLFW_windowSys.h"

#endif // NG_PLATFORM_WINDOWS

namespace Engine {
	// Set static vars
	Application* Application::s_instance = nullptr;
	float Application::s_timestep = 1.0f / 60.0f;
	glm::ivec2 Application::s_screenResolution = glm::ivec2(0, 0);

#pragma region TempGlobalVars
	glm::mat4 FCmodel, TPmodel;
#pragma endregion TempGlobalVars

	Application::Application()
	{
		if (s_instance == nullptr)
		{
			s_instance = this;
		}

		// Start systems 
		m_log.reset(new Log());
		m_log->start();
		m_timer.reset(new Time());
		m_timer->start();
#ifdef NG_PLATFORM_WINDOWS
		m_windows = std::shared_ptr<WindowSystem>(new GLFW_WindowSys());
#endif // NG_PLATFORM_WINDOWS
		m_windows->start();
		LOG_CORE_INFO("Windows system initialised");

		// Create window
		m_window = std::shared_ptr<Window>(Window::create());
		m_window->setEventCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));
		// Set screen res
		Application::s_screenResolution = glm::ivec2(m_window->getWidth(), m_window->getHeight());

#pragma region TempSetup
		//  Temporary set up code to be abstracted

		// Enable standard depth detest (Z-buffer)
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		// Enabling backface culling to ensure triangle vertices are correct ordered (CCW)
		//glEnable(GL_CULL_FACE);
		//glCullFace(GL_BACK);

		float FCvertices[6 * 24] = {
			-0.5f, -0.5f, -0.5f, 0.8f, 0.2f, 0.2f, // red square
			 0.5f, -0.5f, -0.5f, 0.8f, 0.2f, 0.2f,
			 0.5f,  0.5f, -0.5f, 0.8f, 0.2f, 0.2f,
			-0.5f,  0.5f, -0.5f,  0.8f, 0.2f, 0.2f,
			-0.5f, -0.5f, 0.5f, 0.2f, 0.8f, 0.2f, // green square
			 0.5f, -0.5f, 0.5f, 0.2f, 0.8f, 0.2f,
			 0.5f,  0.5f, 0.5f, 0.2f, 0.8f, 0.2f,
			-0.5f,  0.5f, 0.5f,  0.2f, 0.8f, 0.2f,
			-0.5f, -0.5f, -0.5f, 0.8f, 0.2f, 0.8f, // magenta(ish) square
			 0.5f, -0.5f, -0.5f, 0.8f, 0.2f, 0.8f,
			 0.5f, -0.5f, 0.5f, 0.8f, 0.2f, 0.8f,
			-0.5f, -0.5f, 0.5f,  0.8f, 0.2f, 0.8f,
			-0.5f, 0.5f, -0.5f, 0.8f, 0.8f, 0.2f, // yellow square 
			 0.5f, 0.5f, -0.5f, 0.8f, 0.8f, 0.2f,
			 0.5f, 0.5f, 0.5f, 0.8f, 0.8f, 0.2f,
			-0.5f, 0.5f, 0.5f,  0.8f, 0.8f, 0.2f,
			-0.5f, -0.5f, -0.5f, 0.2f, 0.8f, 0.8f, // Cyan(ish) square 
			-0.5f,  0.5f, -0.5f,  0.2f, 0.8f, 0.8f,
			-0.5f,  0.5f, 0.5f, 0.2f, 0.8f, 0.8f,
			-0.5f,  -0.5f, 0.5f, 0.2f, 0.8f, 0.8f,
			0.5f, -0.5f, -0.5f, 0.2f, 0.2f, 0.8f, // Blue square 
			0.5f,  0.5f, -0.5f,  0.2f, 0.2f, 0.8f,
			0.5f,  0.5f, 0.5f, 0.2f, 0.2f, 0.8f,
			0.5f,  -0.5f, 0.5f, 0.2f, 0.2f, 0.8f
		};

		unsigned int indices[3 * 12] = {
			2, 1, 0,
			0, 3, 2,
			4, 5, 6,
			6, 7, 4,
			8, 9, 10,
			10, 11, 8,
			14, 13, 12,
			12, 15, 14,
			18, 17, 16,
			16, 19, 18,
			20, 21, 22,
			22, 23, 20
		};

		bl = { {ShaderDataType::Float3},{ShaderDataType::Float3} };
		vao = std::shared_ptr<OpenGL_VertexArray>(new OpenGL_VertexArray());
		vbo = std::shared_ptr<OpenGL_VertexBuffer>(new OpenGL_VertexBuffer(FCvertices, sizeof(FCvertices), bl));
		vbo->bind();
		ibo = std::shared_ptr<OpenGL_IndexBuffer>(new OpenGL_IndexBuffer(indices, 36));
		ibo->bind();
		vao->setVertexBuffer(vbo);
		vao->setIndexBuffer(ibo);
		vao->bind();

		std::string FCvertSrc = R"(
				#version 440 core
			
				layout(location = 0) in vec3 a_vertexPosition;
				layout(location = 1) in vec3 a_vertexColour;
				out vec3 fragmentColour;
				uniform mat4 u_MVP;
				void main()
				{
					fragmentColour = a_vertexColour;
					gl_Position =  u_MVP * vec4(a_vertexPosition,1);
				}
			)";

		std::string FCFragSrc = R"(
				#version 440 core
			
				layout(location = 0) out vec4 colour;
				in vec3 fragmentColour;
				void main()
				{
					colour = vec4(fragmentColour, 1.0);
				}
		)";

		GLuint FCVertShader = glCreateShader(GL_VERTEX_SHADER);

		const GLchar* source = FCvertSrc.c_str();
		glShaderSource(FCVertShader, 1, &source, 0);
		glCompileShader(FCVertShader);

		GLint isCompiled = 0;
		glGetShaderiv(FCVertShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(FCVertShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(FCVertShader, maxLength, &maxLength, &infoLog[0]);
			LOG_CORE_ERROR("Shader compile error: {0}", std::string(infoLog.begin(), infoLog.end()));

			glDeleteShader(FCVertShader);
			return;
		}

		GLuint FCFragShader = glCreateShader(GL_FRAGMENT_SHADER);

		source = FCFragSrc.c_str();
		glShaderSource(FCFragShader, 1, &source, 0);
		glCompileShader(FCFragShader);

		glGetShaderiv(FCFragShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(FCFragShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(FCFragShader, maxLength, &maxLength, &infoLog[0]);
			LOG_CORE_ERROR("Shader compile error: {0}", std::string(infoLog.begin(), infoLog.end()));

			glDeleteShader(FCFragShader);
			glDeleteShader(FCVertShader);

			return;
		}

		m_FCprogram = glCreateProgram();
		glAttachShader(m_FCprogram, FCVertShader);
		glAttachShader(m_FCprogram, FCFragShader);
		glLinkProgram(m_FCprogram);

		GLint isLinked = 0;
		glGetProgramiv(m_FCprogram, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_FCprogram, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(m_FCprogram, maxLength, &maxLength, &infoLog[0]);
			LOG_CORE_ERROR("Shader linking error: {0}", std::string(infoLog.begin(), infoLog.end()));

			glDeleteProgram(m_FCprogram);
			glDeleteShader(FCVertShader);
			glDeleteShader(FCFragShader);

			return;
		}

		glDetachShader(m_FCprogram, FCVertShader);
		glDetachShader(m_FCprogram, FCFragShader);

		// Added textuer phong shader and cube

		float TPvertices[8 * 24] = {
			-0.5f, -0.5f, -0.5f, 0.f, 0.f, -1.f, 0.33f, 0.5f,
			 0.5f, -0.5f, -0.5f, 0.f, 0.f, -1.f, 0.f, 0.5f,
			 0.5f,  0.5f, -0.5f, 0.f, 0.f, -1.f, 0.f, 0.f,
			-0.5f,  0.5f, -0.5f, 0.f, 0.f, -1.f, 0.33f, 0.f,
			-0.5f, -0.5f, 0.5f,  0.f, 0.f, 1.f, 0.33f, 0.5f,
			 0.5f, -0.5f, 0.5f,  0.f, 0.f, 1.f, 0.66f, 0.5f,
			 0.5f,  0.5f, 0.5f,  0.f, 0.f, 1.f, 0.66f, 0.f,
			-0.5f,  0.5f, 0.5f,  0.f, 0.f, 1.f, 0.33, 0.f,
			-0.5f, -0.5f, -0.5f, 0.f, -1.f, 0.f, 1.f, 0.f,
			 0.5f, -0.5f, -0.5f, 0.f, -1.f, 0.f, 0.66f, 0.f,
			 0.5f, -0.5f, 0.5f,  0.f, -1.f, 0.f, 0.66f, 0.5f,
			-0.5f, -0.5f, 0.5f,  0.f, -1.f, 0.f, 1.0f, 0.5f,
			-0.5f, 0.5f, -0.5f,  0.f, 1.f, 0.f, 0.33f, 1.0f,
			 0.5f, 0.5f, -0.5f,  0.f, 1.f, 0.f, 0.f, 1.0f,
			 0.5f, 0.5f, 0.5f, 0.f, 1.f, 0.f, 0.f, 0.5f,
			-0.5f, 0.5f, 0.5f,   0.f, 1.f, 0.f, 0.3f, 0.5f,
			-0.5f, -0.5f, -0.5f, -1.f, 0.f, 0.f, 0.33f, 1.0f,
			-0.5f,  0.5f, -0.5f, -1.f, 0.f, 0.f, 0.33f, 0.5f,
			-0.5f,  0.5f, 0.5f,  -1.f, 0.f, 0.f, 0.66f, 0.5f,
			-0.5f,  -0.5f, 0.5f, -1.f, 0.f, 0.f, 0.66f, 1.0f,
			0.5f, -0.5f, -0.5f,  1.f, 0.f, 0.f, 1.0f, 1.0f,
			0.5f,  0.5f, -0.5f,  1.f, 0.f, 0.f, 1.0f, 0.5f,
			0.5f,  0.5f, 0.5f, 1.f, 0.f, 0.f,  0.66f, 0.5f,
			0.5f,  -0.5f, 0.5f,  1.f, 0.f, 0.f, 0.66f, 1.0f
		};

		bl1 = { {ShaderDataType::Float3},{ShaderDataType::Float3},{ShaderDataType::Float2} };
		vao1 = std::shared_ptr<OpenGL_VertexArray>(new OpenGL_VertexArray());
		vbo1 = std::shared_ptr<OpenGL_VertexBuffer>(new OpenGL_VertexBuffer(TPvertices, sizeof(TPvertices), bl1));
		vbo1->bind();
		ibo1 = std::shared_ptr<OpenGL_IndexBuffer>(new OpenGL_IndexBuffer(indices, 36));
		ibo1->bind();
		vao1->setVertexBuffer(vbo1);
		vao1->setIndexBuffer(ibo);
		vao1->bind();

		std::string TPvertSrc = R"(
				#version 440 core
			
				layout(location = 0) in vec3 a_vertexPosition;
				layout(location = 1) in vec3 a_vertexNormal;
				layout(location = 2) in vec2 a_texCoord;
				out vec3 fragmentPos;
				out vec3 normal;
				out vec2 texCoord;
				uniform mat4 u_model;
				uniform mat4 u_MVP;
				void main()
				{
					fragmentPos = vec3(u_model * vec4(a_vertexPosition, 1.0));
					normal = mat3(transpose(inverse(u_model))) * a_vertexNormal;
					texCoord = vec2(a_texCoord.x, a_texCoord.y);
					gl_Position =  u_MVP * vec4(a_vertexPosition,1.0);
				}
			)";

		std::string TPFragSrc = R"(
				#version 440 core
			
				layout(location = 0) out vec4 colour;
				in vec3 normal;
				in vec3 fragmentPos;
				in vec2 texCoord;
				uniform vec3 u_lightPos; 
				uniform vec3 u_viewPos; 
				uniform vec3 u_lightColour;
				uniform sampler2D u_texData;
				void main()
				{
					float ambientStrength = 0.4;
					vec3 ambient = ambientStrength * u_lightColour;
					vec3 norm = normalize(normal);
					vec3 lightDir = normalize(u_lightPos - fragmentPos);
					float diff = max(dot(norm, lightDir), 0.0);
					vec3 diffuse = diff * u_lightColour;
					float specularStrength = 0.8;
					vec3 viewDir = normalize(u_viewPos - fragmentPos);
					vec3 reflectDir = reflect(-lightDir, norm);  
					float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64);
					vec3 specular = specularStrength * spec * u_lightColour;  
					
					colour = vec4((ambient + diffuse + specular), 1.0) * texture(u_texData, texCoord);
				}
		)";

		GLuint TPVertShader = glCreateShader(GL_VERTEX_SHADER);

		source = TPvertSrc.c_str();
		glShaderSource(TPVertShader, 1, &source, 0);
		glCompileShader(TPVertShader);

		isCompiled = 0;
		glGetShaderiv(TPVertShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(TPVertShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(TPVertShader, maxLength, &maxLength, &infoLog[0]);
			LOG_CORE_ERROR("Shader compile error: {0}", std::string(infoLog.begin(), infoLog.end()));

			glDeleteShader(TPVertShader);
			return;
		}

		GLuint TPFragShader = glCreateShader(GL_FRAGMENT_SHADER);

		source = TPFragSrc.c_str();
		glShaderSource(TPFragShader, 1, &source, 0);
		glCompileShader(TPFragShader);

		glGetShaderiv(TPFragShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(TPFragShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(TPFragShader, maxLength, &maxLength, &infoLog[0]);
			LOG_CORE_ERROR("Shader compile error: {0}", std::string(infoLog.begin(), infoLog.end()));

			glDeleteShader(TPFragShader);
			glDeleteShader(TPVertShader);

			return;
		}

		m_TPprogram = glCreateProgram();
		glAttachShader(m_TPprogram, TPVertShader);
		glAttachShader(m_TPprogram, TPFragShader);
		glLinkProgram(m_TPprogram);

		isLinked = 0;
		glGetProgramiv(m_TPprogram, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_TPprogram, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(m_TPprogram, maxLength, &maxLength, &infoLog[0]);
			LOG_CORE_ERROR("Shader linking error: {0}", std::string(infoLog.begin(), infoLog.end()));

			glDeleteProgram(m_TPprogram);
			glDeleteShader(TPVertShader);
			glDeleteShader(TPFragShader);

			return;
		}

		glDetachShader(m_TPprogram, FCVertShader);
		glDetachShader(m_TPprogram, FCFragShader);

		FCmodel = glm::translate(glm::mat4(1), glm::vec3(1.5, 0, 3));
		TPmodel = glm::translate(glm::mat4(1), glm::vec3(-1.5, 0, 3));

		// End temporary code

		tex = std::shared_ptr<OpenGL_Texture>(new OpenGL_Texture("assets/textures/letterCube.png"));
		tex->bind();
		tex1 = std::shared_ptr<OpenGL_Texture>(new OpenGL_Texture("assets/textures/numberCube.png"));
		tex1->bind();

#pragma endregion TempSetup

		// Reset timer
		m_timer->getDeltaTime();
	}

	Application::~Application()
	{
		// Stop systems
		m_timer->stop();
		m_log->stop();
	}

	void Application::onEvent(Event& e)
	{
		LOG_CORE_INFO("Event: {0}", e.getEventType());

		EventDispatcher dispatcher(e);
		dispatcher.dispatch<WindowClose>(std::bind(&Application::onClose, this, std::placeholders::_1));
		dispatcher.dispatch<WindowResize>(std::bind(&Application::onResize, this, std::placeholders::_1));
		dispatcher.dispatch<KeyPressed>(std::bind(&Application::onKeyPressed, this, std::placeholders::_1));
	}

	bool Application::onClose(WindowClose& e)
	{
		LOG_CORE_INFO("Closing application");
		m_running = false;
		return true;
	}

	bool Application::onResize(WindowResize& e)
	{
		m_window->onResize(e.getWidth(), e.getHeight());
		return true;
	}

	bool Application::onKeyPressed(KeyPressed& e)
	{
		if (e.getButton() == KEY_ESCAPE) //Escape
		{
			m_running = false;
			return true;
		}
		if (e.getButton() == KEY_TAB)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			return true;
		}
		return false;
	}

	void Application::run()
	{

		while (m_running)
		{
			//LOG_CORE_INFO("FPS: {0}", (int)(1.0f / s_timestep));

#pragma region TempDrawCode
			// Temporary draw code to be abstracted

			glClearColor(0.8f, 0.8f, 0.8f, 1);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glm::mat4 projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f); // Basic 4:3 camera

			glm::mat4 view = glm::lookAt(
				glm::vec3(0.0f, 0.0f, -4.5f), // Camera is at (0.0,0.0,-4.5), in World Space
				glm::vec3(0.f, 0.f, 0.f), // and looks at the origin
				glm::vec3(0.f, 1.f, 0.f)  // Standing straight  up
			);

			// Code to make the cube move, you can ignore this more or less.
			glm::mat4 FCtranslation, TPtranslation;

			if (m_goingUp)
			{
				FCtranslation = glm::translate(FCmodel, glm::vec3(0.0f, 0.2f * s_timestep, 0.0f));
				TPtranslation = glm::translate(TPmodel, glm::vec3(0.0f, -0.2f * s_timestep, 0.0f));
			}
			else
			{
				FCtranslation = glm::translate(FCmodel, glm::vec3(0.0f, -0.2f * s_timestep, 0.0f));
				TPtranslation = glm::translate(TPmodel, glm::vec3(0.0f, 0.2f * s_timestep, 0.0f));
			}

			m_timeSummed += s_timestep;
			if (m_timeSummed > 20.0f) {
				m_timeSummed = 0.f;
				m_goingUp = !m_goingUp;
			}


			FCmodel = glm::rotate(FCtranslation, glm::radians(20.f) * s_timestep, glm::vec3(0.f, 1.f, 0.f)); // Spin the cube at 20 degrees per second
			TPmodel = glm::rotate(TPtranslation, glm::radians(-20.f) * s_timestep, glm::vec3(0.f, 1.f, 0.f)); // Spin the cube at 20 degrees per second

			// End of code to make the cube move.

			glm::mat4 fcMVP = projection * view * FCmodel;
			glUseProgram(m_FCprogram);



			vao->bind();

			GLuint MVPLoc = glGetUniformLocation(m_FCprogram, "u_MVP");
			glUniformMatrix4fv(MVPLoc, 1, GL_FALSE, &fcMVP[0][0]);
			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);

			glm::mat4 tpMVP = projection * view * TPmodel;
			unsigned int texSlot;
			if (m_goingUp) texSlot = 0;
			else texSlot = 1;

			glUseProgram(m_TPprogram);
			vao1->bind();

			MVPLoc = glGetUniformLocation(m_TPprogram, "u_MVP");
			glUniformMatrix4fv(MVPLoc, 1, GL_FALSE, &tpMVP[0][0]);

			GLuint modelLoc = glGetUniformLocation(m_TPprogram, "u_model");
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &TPmodel[0][0]);

			GLuint colLoc = glGetUniformLocation(m_TPprogram, "u_objectColour");
			glUniform3f(colLoc, 0.2f, 0.8f, 0.5f);

			GLuint lightColLoc = glGetUniformLocation(m_TPprogram, "u_lightColour");
			glUniform3f(lightColLoc, 1.0f, 1.0f, 1.0f);

			GLuint lightPosLoc = glGetUniformLocation(m_TPprogram, "u_lightPos");
			glUniform3f(lightPosLoc, 1.0f, 4.0f, -6.0f);

			GLuint viewPosLoc = glGetUniformLocation(m_TPprogram, "u_viewPos");
			glUniform3f(viewPosLoc, 0.0f, 0.0f, -4.5f);

			GLuint texDataLoc = glGetUniformLocation(m_TPprogram, "u_texData");
			glUniform1i(texDataLoc, texSlot);
			glDrawElements(GL_TRIANGLES, 3 * 12, GL_UNSIGNED_INT, nullptr);

			// End temporary code
#pragma endregion TempDrawCode

			m_window->onUpdate(s_timestep);
		}
	}

}