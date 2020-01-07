#include "engine_pch.h"
#include "systems/log.h"
#include "layers/layer.h"

namespace Engine
{

	Layer::Layer(const std::string& name) : m_name(name)
	{
		LOG_CORE_INFO("LAYER ADDED '{0}'", name);
	}

}