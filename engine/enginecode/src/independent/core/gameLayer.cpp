#include "engine_pch.h"
#include "systems/log.h"
#include "core/gameLayer.h"

namespace Engine
{

	void GameLayer::onAttach()
	{
	}

	void GameLayer::onDetach()
	{

	}

	void GameLayer::onUpdate(float timestep)
	{
		LOG_CORE_INFO("GAME LAYER TIMESTEP = '{0}'", timestep);
	}

	void GameLayer::onEvent(Event& e)
	{

	}

}