#include "engine_pch.h"
#include "systems/log.h"
#include "layers/layer.h"

namespace Engine
{

	Layer::Layer(const std::string& name) : m_name(name)
	{
#ifdef NG_DEBUG
		LOG_CORE_INFO("LAYER ADDED '{0}'", name);
#endif // NG_DEBUG
	}

}