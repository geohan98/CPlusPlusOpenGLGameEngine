#include "engine_pch.h"
#include "gameLayer.h"
#include "Headers/systems/log.h"
#include "Headers/cameras/cameraController3D.h"

namespace Engine
{
	void GameLayer::onAttach()
	{
		m_resourceManager = std::shared_ptr<Systems::ResourceManager>(new Systems::ResourceManager());
		m_resourceManager->start();
		m_renderer = std::shared_ptr<Renderer::Renderer>(Renderer::Renderer::createBasic3D());
		m_renderer->actionCommand(Renderer::RenderCommand::setClearColourCommand(0.9, 0.9, 0.9, 1.0f));
		m_camera = std::shared_ptr<CameraController3D>(new CameraController3D);
		m_camera->init(80.0f, 800.0f / 600.0f, 0.1, 100.0f);

		m_gameObjects.push_back(std::shared_ptr<GameObject>(new GameObject()));
		m_positionComponents.push_back(std::shared_ptr<PositionComponent>(new PositionComponent(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f))));
		m_particleComponents.push_back(std::shared_ptr<Components::ParticleComponent>(new Components::ParticleComponent()));
		m_gameObjects.back()->addComponent(m_positionComponents.back());
		m_gameObjects.back()->addComponent(m_particleComponents.back());

		Renderer::UniformBufferLayout viewProjectionLayout = { Renderer::ShaderDataType::Mat4,Renderer::ShaderDataType::Mat4 };
		auto viewProjectionBuffer = std::shared_ptr<Renderer::UniformBuffer>(Renderer::UniformBuffer::create(viewProjectionLayout.getStride(), viewProjectionLayout));

		viewProjectionBuffer->attachShaderBlock(m_particleComponents.back()->getMaterial()->getShader(), "VP");
		std::vector<void*> viewProjectionData(2);
		viewProjectionData[0] = (void*)&m_camera->getCamera()->getProjection();
		viewProjectionData[1] = (void*)&m_camera->getCamera()->getView();
		m_sceneData[viewProjectionBuffer] = viewProjectionData;
	}

	void GameLayer::onDetach()
	{

	}

	void GameLayer::onUpdate(float deltaTime)
	{
		m_renderer->beginScene(m_sceneData);

		m_camera->onUpdate(deltaTime);
		for (auto& CGO : m_gameObjects)
		{
			CGO->onUpdate(deltaTime);
		}

		m_renderer->actionCommand(Renderer::RenderCommand::setDepthTestLessCommand(true));
		m_renderer->actionCommand(Renderer::RenderCommand::setBackFaceCullingCommand(true));
		m_renderer->actionCommand(Renderer::RenderCommand::ClearDepthColourBufferCommand());
	}

	void GameLayer::onEvent(Events::Event& e)
	{
		//Send Event to Camera Controller
		m_camera->onEvent(e);
		//Send Event to All Game Objects
		for (auto& CGO : m_gameObjects) CGO->onEvent(e);
	}

}