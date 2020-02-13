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
		m_particleComponents.push_back(std::shared_ptr<Components::ParticleComponent>(new Components::ParticleComponent()));
		m_gameObjects.back()->addComponent(m_particleComponents.back());



		Renderer::UniformBufferLayout cameraUniformLayout = { Renderer::ShaderDataType::Mat4,Renderer::ShaderDataType::Mat4 };
		auto cameraUniformBuffer = std::shared_ptr<Renderer::UniformBuffer>(Renderer::UniformBuffer::create(cameraUniformLayout.getStride(), cameraUniformLayout));

		//cameraUniformBuffer->attachShaderBlock(m_resourceManager->getMaterial("FC_CUBE")->getShader(), "Matrices");
		std::vector<void*> cameraSceneData(2);
		cameraSceneData[0] = (void*)&m_camera->getCamera()->getProjection();
		cameraSceneData[1] = (void*)&m_camera->getCamera()->getView();

		/*std::vector<int> xXxSephirothxXx;
		xXxSephirothxXx.push_back(0);
		int * start = &xXxSephirothxXx[0];
		LOG_CORE_INFO("TEST, size: {0}, capacity {1}, start address {2}", xXxSephirothxXx.size(), xXxSephirothxXx.capacity(), (int)start);
		unsigned int blockCount = 0;
		for (unsigned int i = 0; i < 100; i++) {
			xXxSephirothxXx.push_back(0);
			if (start != &xXxSephirothxXx[0]) {
				LOG_CORE_CRITICAL("AaAaH wE mOveD!1!! (Block count {0})", blockCount);
				start = &xXxSephirothxXx[0];
				blockCount = 0;
			}
			blockCount++;
			LOG_CORE_INFO("TEST, size: {0}, capacity {1}, start address {2}", xXxSephirothxXx.size(), xXxSephirothxXx.capacity(), (int)start);
		}*/

		m_sceneData[cameraUniformBuffer] = cameraSceneData;

		Renderer::UniformBufferLayout LightUniformLayout = { Renderer::ShaderDataType::Float3 };
		auto lightUniformBuffer = std::shared_ptr<Renderer::UniformBuffer>(Renderer::UniformBuffer::create(LightUniformLayout.getStride(), LightUniformLayout));

		//lightUniformBuffer->attachShaderBlock(m_resourceManager->getMaterial("FC_CUBE")->getShader(), "Lights");
		std::vector<void*> lightSceneData(1);
		lightSceneData[0] = (void*)&colour;
		m_sceneData[lightUniformBuffer] = lightSceneData;
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