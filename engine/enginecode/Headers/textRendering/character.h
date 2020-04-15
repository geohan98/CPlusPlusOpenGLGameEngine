#pragma once
#include "glm/glm.hpp"

namespace Engine
{
	class Character
	{
	private:
		glm::vec2 m_startUV;
		glm::vec2 m_endUV;
		glm::ivec2 m_size;
		glm::ivec2 m_bearing;
		int m_advance;
	public:
		Character() {};
		Character(glm::ivec2 _size, glm::ivec2 _bearing, int adavance, glm::vec2 _startUV = glm::vec2(0.0f, 0.0f), glm::vec2 _endUV = glm::vec2(0.0f, 0.0f)) :
			m_startUV(m_startUV), m_endUV(m_endUV), m_size(_size), m_bearing(_bearing), m_advance(m_advance) {}
		void setUVs(glm::vec2 _startUV, glm::vec2 _endUV) { m_startUV = _startUV; m_endUV = _endUV; }
		inline glm::vec2 getStartUV() { return m_startUV; }
		inline glm::vec2 getEndUV() { return m_endUV; }
		inline glm::ivec2 getSize() { return m_size; }
		inline glm::ivec2 getBearing() { return m_bearing; }
		inline int getAdvance() { return m_advance; }
	};
}