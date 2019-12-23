#include "engine_pch.h"
#include "systems/log.h"
#include "core/perspectiveCamera3D.h"

namespace Engine
{

	void PerspectiveCamera3D::updateView()
	{

	}

	PerspectiveCamera3D::PerspectiveCamera3D(float fov, float aspectRatio, float nearClip, float farClip)
	{
		m_projection = glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip);
		m_viewProjection = m_projection * m_view;
	}

	void PerspectiveCamera3D::reset(float fov, float aspectRatio, float nearClip, float farClip)
	{
		m_projection = glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip);
	}

}