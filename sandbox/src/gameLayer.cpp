#include "engine_pch.h"
#include "gameLayer.h"
#include "../enginecode/Headers/cameras/cameraController3D.h"
#include "../enginecode/Headers/fileLoaders/textLoader.h"
#include "../enginecode/Headers/fileLoaders/JSONLoaderLog.h"
#include "../enginecode/Headers/assetloader.h"

#include "../imgui/imgui.h"

#pragma message("Includes complete.")

namespace Engine
{
	void GameLayer::onAttach()
	{
		TextModel mesh;
		std::string filepath = "assets/models/fccube.txt";
		TextLoader::loadModel(m_resourceManager, filepath, mesh);
		//std::string ourModel = ("Propane_LOD3.obj");
		//AssetLoader ourModel("assets/models/Propane_LOD3.obj");

		m_resourceManager = std::shared_ptr<Systems::ResourceManager>(new Systems::ResourceManager());
		m_resourceManager->start();

		m_renderer = std::shared_ptr<Renderer::Renderer>(Renderer::Renderer::createBasic3D());
		m_renderer->actionCommand(Renderer::RenderCommand::setClearColourCommand(0.0, 0.0, 0.0, 1.0f));

		m_predrawCommands.push_back(std::shared_ptr<Renderer::RenderCommand>(Renderer::RenderCommand::setDepthTestLessCommand(true, false)));
		m_predrawCommands.push_back(std::shared_ptr<Renderer::RenderCommand>(Renderer::RenderCommand::setBlendMode(true, false)));
		m_predrawCommands.push_back(std::shared_ptr<Renderer::RenderCommand>(Renderer::RenderCommand::setBackFaceCullingCommand(true, false)));
		m_predrawCommands.push_back(std::shared_ptr<Renderer::RenderCommand>(Renderer::RenderCommand::ClearDepthColourBufferCommand(false)));

		m_gameObjects.push_back(std::shared_ptr<GameObject>(new GameObject));
		m_positionComponents.push_back(std::shared_ptr<PositionComponent>(new PositionComponent(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f))));
		m_materials.push_back(std::shared_ptr<MaterialComponent>(new MaterialComponent(m_resourceManager->getMaterial("FC_CUBE"))));
		m_physicsComponent.push_back(std::shared_ptr<PhysicsComponent>(new PhysicsComponent(glm::vec3(0.5,0.5,0.5),glm::vec3(0,0,5.0f))));

		m_gameObjects.back()->addComponent(m_positionComponents.back());
		m_gameObjects.back()->addComponent(m_physicsComponent.back());
		m_gameObjects.back()->addComponent(m_materials.back());

		m_camera = std::shared_ptr<CameraController3D>(new CameraController3D);
		m_camera->init(80.0f, 800.0f / 600.0f, 0.1, 100.0f);

		m_gameObjects.push_back(std::shared_ptr<GameObject>(new GameObject()));
		m_positionComponents.push_back(std::shared_ptr<PositionComponent>(new PositionComponent(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f))));
		m_particleComponents.push_back(std::shared_ptr<Components::ParticleComponent>(new Components::ParticleComponent()));
		m_gameObjects.back()->addComponent(m_positionComponents.back());
		
		if (!m_particleComponents.empty())
		{
			m_gameObjects.back()->addComponent(m_particleComponents.back());
		}

		

		Renderer::UniformBufferLayout viewProjectionLayout = { Renderer::ShaderDataType::Mat4,Renderer::ShaderDataType::Mat4 };
		auto viewProjectionBuffer = std::shared_ptr<Renderer::UniformBuffer>(Renderer::UniformBuffer::create(viewProjectionLayout.getStride(), viewProjectionLayout));

		if (!m_particleComponents.empty())
		{
			viewProjectionBuffer->attachShaderBlock(m_particleComponents.back()->getMaterial()->getShader(), "VP");
			std::vector<void*> viewProjectionData(2);
			viewProjectionData[0] = (void*)&m_camera->getCamera()->getProjection();
			viewProjectionData[1] = (void*)&m_camera->getCamera()->getView();
			m_sceneData[viewProjectionBuffer] = viewProjectionData;
		}
	}
#pragma message("GameLayer::onAttach() complete.")

	void GameLayer::onDetach()
	{
		LOG_INFO("[GAMELAYER][DETACH]");
	}
#pragma message("GameLayer::onDetach() complete.")

	void GameLayer::onUpdate(float deltaTime)
	{
		m_camera->onUpdate(deltaTime);
		for (auto& CGO : m_gameObjects)
		{
			CGO->onUpdate(deltaTime);
		}

		m_renderer->beginScene(m_sceneData);

		for (auto& renderCommand : m_predrawCommands)
		{
			m_renderer->actionCommand(renderCommand.get());
		}

		if (!m_particleComponents.empty())
		{
			m_renderer->submit(m_particleComponents.back()->getMaterial());
		}

		for (auto& renderCommand : m_postdrawCommands)
		{
			m_renderer->actionCommand(renderCommand.get());
		}


	}
#pragma message("GameLayer::onUpdate() complete.")

	void GameLayer::onEvent(Events::Event& e)
	{
		//Send Event to Camera Controller
		m_camera->onEvent(e);
		//Send Event to All Game Objects
		for (auto& CGO : m_gameObjects) CGO->onEvent(e);
	}
#pragma message("GameLayer::onEvent() complete.")
}