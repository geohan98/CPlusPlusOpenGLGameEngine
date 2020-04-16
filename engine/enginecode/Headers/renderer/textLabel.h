#pragma once
#include <string>
#include "glm/glm.hpp"
#include <memory>
#include "Headers/renderer/material.h"

namespace Engine
{
	class TextLabel
	{
	public:
		virtual bool setFont(const std::string& fontName) = 0;
		virtual bool setCharSize(unsigned int charSize) = 0;
		virtual void setText(const std::string& text) = 0;
		virtual void setPosition(const glm::vec2& position) = 0;
		virtual void setOrientation(const float angle) = 0;
		virtual void setScale(const float scale) = 0;
		virtual void setColour(const glm::vec3& colour) = 0;
		virtual const std::string& getFont() const = 0;
		virtual unsigned int getCharSize() = 0;
		virtual const std::string& getText() = 0;
		virtual glm::vec2 getPosition() = 0;
		virtual float getOrientation() = 0;
		virtual float getScale() = 0;
		virtual glm::vec3 getColour() = 0;
		virtual glm::mat4 getModel() const = 0;
		virtual std::shared_ptr<Renderer::Material> getMaterial() const = 0;

		static std::shared_ptr<TextLabel> create(const std::string& fontName, unsigned int charSize, const std::string& text, const glm::vec2& position, float orientatiom, float scale, const glm::vec3& colour);
	private:
	};
}