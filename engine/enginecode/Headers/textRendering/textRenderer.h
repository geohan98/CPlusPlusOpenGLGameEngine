#pragma once

#include "../freetype2/include/ft2build.h"
#include FT_FREETYPE_H

#include <iostream>
#include <map>
#include <string>

#include "Headers/systems/system.h"

#define GLEW_STATIC
#include "glad/glad.h"

//GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Headers/OpenGL/OpenGL_shader.h"

namespace Engine {
	namespace Systems {
		struct Character {
			GLuint TextureID;   // ID handle of the glyph texture
			glm::ivec2 Size;    // Size of glyph
			glm::ivec2 Bearing;  // Offset from baseline to left/top of glyph
			GLuint Advance;    // Horizontal offset to advance to next glyph
		};

		std::map<GLchar, Character> Characters;
		GLuint VAO, VBO;

		class textRenderer : public System {
		public:
			textRenderer();
			void start(SystemSignal init = SystemSignal::None, ...);
			void stop(SystemSignal init = SystemSignal::None, ...);
			
			Engine::Renderer::OpenGL_Shader shader;

			void update();

			void RenderText(Engine::Renderer::OpenGL_Shader &shader, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
		};
	}
}