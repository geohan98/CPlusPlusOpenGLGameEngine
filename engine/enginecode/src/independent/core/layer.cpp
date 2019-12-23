#include "engine_pch.h"
#include "systems/log.h"
#include "core/layer.h"

namespace Engine
{

	Layer::Layer(std::string name) : m_name(name)
	{
		LOG_CORE_INFO("LAYER ADDED '{0}'", name);
	}

}