#include "engine_pch.h"
#include "meshLayer.h"
#include "Headers/ASSIMPLoaderLog.h"

namespace Engine
{
#pragma region Attach & Detach

	void MeshLayer::onAttach()
	{
		Loader::ASSIMPLog("assets/models/lettercube/letterCube.obj");
	}
	void MeshLayer::onDetach()
	{
	}

#pragma endregion

#pragma region Update & Event

	void MeshLayer::onUpdate(float deltaTime)
	{
	}
	void MeshLayer::onEvent(Events::Event& e)
	{
	}

#pragma endregion
}