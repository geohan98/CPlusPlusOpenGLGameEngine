#include "engine_pch.h"
#include "../enginecode/Headers/systems/log.h"
#include "../enginecode/Headers/OpenGL/OpenGL_shader.h"
#include "../enginecode/Headers/renderer/vertexBufferLayout.h"
#include <glad/glad.h>

#include <iostream>
#include <fstream>

namespace Engine
{
	namespace Renderer {
		OpenGL_Shader::OpenGL_Shader(const std::string& filepath) : m_rendererID(0)
		{
			parseSource(filepath);
			LOG_CORE_INFO("[OpenGL][SHADER][SHADER CREATED WITH ID:{0}]", m_rendererID);
		}
		OpenGL_Shader::~OpenGL_Shader()
		{
			glDeleteShader(m_rendererID);
			LOG_CORE_INFO("[OpenGL][SHADER][SHADER DESTROYED WITH ID:{0}]", m_rendererID);
		}

		void OpenGL_Shader::bind()
		{
			glUseProgram(m_rendererID);
		}
		void OpenGL_Shader::unbind()
		{
			glUseProgram(0);
		}
		unsigned int OpenGL_Shader::getId()
		{
			return m_rendererID;
		}

		void OpenGL_Shader::parseSource(const std::string& filepath)
		{
			std::fstream handle(filepath, std::ios::in);
			enum { NONE = -1, VERTEX = 0, FRAGMENT, GEOMATRY, TESSALATION_CONTROL, TESSALATION_EVALUATION } region;
			if (!handle.is_open())
			{
#ifdef NG_DEBUG
				LOG_CORE_ERROR("[OpenGL][SHADER][ COULD NOT OPEN SHADER FILE: '{0}']", filepath);
#endif // NG_DEBUG
			}

			std::string line, src[5];

			while (getline(handle, line))
			{
				if (line.find("#region Vertex") != std::string::npos) { region = VERTEX; continue; }
				if (line.find("#region Fragment") != std::string::npos) { region = FRAGMENT; continue; }
				if (line.find("#region Geomatry") != std::string::npos) { region = GEOMATRY; continue; }
				if (line.find("#region Tessalation_Control") != std::string::npos) { region = TESSALATION_CONTROL; continue; }
				if (line.find("#region Tessalation_Evaluation") != std::string::npos) { region = TESSALATION_EVALUATION; continue; }

				if (line.find(" in ") != std::string::npos && region == VERTEX)
				{
					std::string x = line;
					x = x.substr(x.find("in") + 3);
					x = x.erase(x.find(" "));
					//LOG_CORE_INFO(x);
					m_bufferlayout.addElement(GLSLStrToSDT(x));
				}

				if (line.find("uniform ") != std::string::npos && line.find("layout") == std::string::npos)
				{
					std::string x = line;
					x = x.substr(x.find("uniform") + 8);
					std::string y = x;
					x = x.erase(x.find(" "));

					y = y.substr(x.size() + 1, y.find(";"));
					y = y.erase(y.find(";"));
					//LOG_CORE_INFO(x);
					//LOG_CORE_INFO(y);
					m_uniformLocationCache[y].first = GLSLStrToSDT(x);
					m_uniformLocationCache[y].second = -1;
				}


				if (region != NONE) src[region] += (line + "\n");
			}

			handle.close();

			compileAndLink(src[VERTEX], src[FRAGMENT], src[GEOMATRY], src[TESSALATION_CONTROL], src[TESSALATION_EVALUATION]);
		}
		void OpenGL_Shader::compileAndLink(std::string& vertex, std::string& fragment, std::string& geomatry, std::string& tessalationControl, std::string& tessalationEvaluation)
		{
			m_rendererID = glCreateProgram();

#pragma region VERTEX SHADER
			unsigned int VS = glCreateShader(GL_VERTEX_SHADER);
			const char* src = vertex.c_str();
			glShaderSource(VS, 1, &src, NULL);
			glCompileShader(VS);
			if (!checkCompileErrors(VS, false))
			{
				glDeleteShader(VS);
				glDeleteProgram(m_rendererID);
				return;
			}
			LOG_CORE_TRACE("[OpenGL][SHADER][COMPILED VERTX SHADER SOURCE]");
			glAttachShader(m_rendererID, VS);
#pragma endregion

#pragma region GEOMATRY SHADER
			unsigned int GS;
			if (!geomatry.empty())
			{
				GS = glCreateShader(GL_GEOMETRY_SHADER);
				src = geomatry.c_str();
				glShaderSource(GS, 1, &src, NULL);
				glCompileShader(GS);
				if (!checkCompileErrors(GS, false))
				{

					glDeleteShader(VS);
					glDeleteShader(GS);
					glDeleteProgram(m_rendererID);
					return;
				}
				LOG_CORE_TRACE("[OpenGL][SHADER][COMPILED GEOMETRY SHADER SOURCE]");
				glAttachShader(m_rendererID, GS);
			}
#pragma endregion

#pragma region TESSALTION CONTROL SHADER
			unsigned int TC;
			if (!tessalationControl.empty())
			{
				TC = glCreateShader(GL_TESS_CONTROL_SHADER);
				src = geomatry.c_str();
				glShaderSource(TC, 1, &src, NULL);
				glCompileShader(TC);
				if (!checkCompileErrors(TC, false))
				{
					glDeleteShader(VS);
					if (!geomatry.empty())
					{
						glDeleteShader(GS);
					}
					glDeleteShader(TC);
					glDeleteProgram(m_rendererID);
					return;
				}
				LOG_CORE_TRACE("[OpenGL][SHADER][COMPILED TESS CONTROL SHADER SOURCE]");
				glAttachShader(m_rendererID, TC);
			}
#pragma endregion

#pragma region TESSALATION EVALUATION SHADER
			unsigned int TE;
			if (!tessalationEvaluation.empty())
			{
				TE = glCreateShader(GL_TESS_EVALUATION_SHADER);
				src = geomatry.c_str();
				glShaderSource(TE, 1, &src, NULL);
				glCompileShader(TE);
				if (!checkCompileErrors(TE, false))
				{
					glDeleteShader(VS);
					if (!geomatry.empty())
					{
						glDeleteShader(GS);
					}
					if (!tessalationControl.empty())
					{
						glDeleteShader(TC);
					}
					glDeleteShader(TE);
					glDeleteProgram(m_rendererID);
					return;
				}
				LOG_CORE_TRACE("[OpenGL][SHADER][COMPILED TESS EVALUATION SHADER SOURCE]");
				glAttachShader(m_rendererID, TE);
			}
#pragma endregion

#pragma region FRAGMENT SHADER
			unsigned int FS = glCreateShader(GL_FRAGMENT_SHADER);
			src = fragment.c_str();
			glShaderSource(FS, 1, &src, NULL);
			glCompileShader(FS);
			if (!checkCompileErrors(FS, false))
			{
				glDeleteShader(VS);
				if (!geomatry.empty())
				{
					glDeleteShader(GS);
				}
				if (!tessalationControl.empty())
				{
					glDeleteShader(TC);
				}
				if (!tessalationControl.empty())
				{
					glDeleteShader(TE);
				}
				glDeleteShader(FS);
				glDeleteProgram(m_rendererID);
				return;
			}
			LOG_CORE_TRACE("[OpenGL][SHADER][COMPILED FRAGMENT SHADER SOURCE]");
			glAttachShader(m_rendererID, FS);
#pragma endregion

#pragma region PROGRAME LINKING
			glLinkProgram(m_rendererID);

			glDeleteShader(VS);
			glDeleteShader(FS);
			if (!geomatry.empty())
			{
				glDeleteShader(GS);
			}
			if (!tessalationControl.empty())
			{
				glDeleteShader(TC);
			}
			if (!tessalationEvaluation.empty())
			{
				glDeleteShader(TE);
			}
			if (!checkCompileErrors(m_rendererID, true))
			{
				glDeleteProgram(m_rendererID);
				return;
			}
#pragma endregion

			setUniformLocations();
		}
		bool OpenGL_Shader::checkCompileErrors(unsigned int shader, bool program)
		{
			int success;
			char info[1024];
			if (program)
			{
				glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
				if (!success)
				{
					glGetShaderInfoLog(shader, 1024, NULL, info);
					LOG_CORE_ERROR("[OpenGL][SHADER][SHADER LINKING ERROR:{0}]", info);
					return false;
				}
			}
			else
			{
				glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
				if (!success)
				{
					glGetShaderInfoLog(shader, 1024, NULL, info);
					LOG_CORE_ERROR("[OpenGL][SHADER][SHADER COMPILE ERROR:{0}]", info);
					return  false;
				}
			}
			return true;
		}
		void OpenGL_Shader::setUniformLocations()
		{
			std::map<std::string, std::pair<ShaderDataType, int>>::iterator it;

			for (auto it = m_uniformLocationCache.begin(); it != m_uniformLocationCache.end(); ++it)
			{
				if (it->second.second == -1)
				{
					it->second.second = glGetUniformLocation(m_rendererID, it->first.c_str());
#ifdef NG_DEBUG
					LOG_CORE_TRACE("[OpenGL][SHADER][UNIFORM CACHED, '{0}', TYPE == '{1}', LOCATION == '{2}']", it->first, it->second.first, it->second.second);
#endif // NG_DEBUG
					if (it->second.second == -1)
					{
#ifdef NG_DEBUG
						LOG_CORE_ERROR("[OpenGL][SHADER][UNIFORM '{0}', DOES NOT EXSIST]", it->first);
#endif // NG_DEBUG
					}
				}
			}
		}
		void OpenGL_Shader::dispatchUniformUpload(ShaderDataType type, unsigned int location, void* data)
		{
			const float* addrf;
			const int* addri;
			float valueFloat;
			int valueInt;

			switch (type)
			{
			case ShaderDataType::None:
#ifdef NG_DEBUG
				LOG_CORE_ERROR("[OpenGL][SHADER][UNIFORM TYPE NOT SPECIFIED]");
#endif // NG_DEBUG
				break;
			case ShaderDataType::Int:
				valueInt = *(int*)data;
				glUniform1i(location, valueInt);
				break;
			case ShaderDataType::Int2:
				addri = (const int*)data;
				glUniform2iv(location, 1, addri);
				break;
			case ShaderDataType::Int3:
				addri = (const int*)data;
				glUniform3iv(location, 1, addri);
				break;
			case ShaderDataType::Int4:
				addri = (const int*)data;
				glUniform4iv(location, 1, addri);
				break;
			case ShaderDataType::Float:
				valueFloat = *(float*)data;
				glUniform1f(location, valueFloat);
				break;
			case ShaderDataType::Float2:
				addrf = (const float*)data;
				glUniform2fv(location, 1, addrf);
				break;
			case ShaderDataType::Float3:
				addrf = (const float*)data;
				glUniform3fv(location, 1, addrf);
				break;
			case ShaderDataType::Float4:
				addrf = (const float*)data;
				glUniform4fv(location, 1, addrf);
				break;
			case ShaderDataType::Mat3:
				addrf = (const float*)data;
				glUniformMatrix3fv(location, 1, GL_FALSE, addrf);
				break;
			case ShaderDataType::Mat4:
				addrf = (const float*)data;
				glUniformMatrix4fv(location, 1, GL_FALSE, addrf);
				break;
			case ShaderDataType::Bool:
				valueInt = *(bool*)data;
				glUniform1i(location, valueInt);
				break;
			case ShaderDataType::Sampler2D:
				valueInt = *(int*)data;
				glUniform1i(location, valueInt);
				break;
			}
		}
		bool OpenGL_Shader::uploadData(const std::string& name, void* data)
		{
			dispatchUniformUpload(m_uniformLocationCache[name].first, m_uniformLocationCache[name].second, data);
			return false;
		}

		VertexBufferLayout OpenGL_Shader::getBufferLayout() const
		{
			return m_bufferlayout;
		}
		UniformLayout OpenGL_Shader::getUniformLayout() const
		{
			return m_uniformLayout;
		}
	}
}