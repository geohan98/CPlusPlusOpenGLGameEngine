#include "engine_pch.h"
#include "gameLayer.h"
#include "Headers/cameras/cameraController3D.h"
#include "Headers/fileLoaders/textLoader.h"

#pragma message("Includes complete.")

namespace Engine
{
	void GameLayer::onAttach()
	{
		LOG_INFO("[GAMELAYER][ATTACH]");
		m_resourceManager = std::shared_ptr<Systems::ResourceManager>(new Systems::ResourceManager());
		m_renderer = std::shared_ptr<Renderer::Renderer>(Renderer::Renderer::createBasic3D());
		m_camera = std::shared_ptr<CameraController>(new CameraController3D());
		m_camera->init(90.0f, 1280.0f / 720.0f, 0.1f, 100.0f);

		m_predrawCommands.push_back(std::shared_ptr<Renderer::RenderCommand>(Renderer::RenderCommand::ClearDepthColourBufferCommand(false)));

		TextModel mesh;
		TextLoader::loadModel(m_resourceManager, "assets/models/fccube.txt", mesh);

		m_resourceManager->addVertexArray("VAO1");
		m_resourceManager->addVertexBuffer("VBO1", mesh.vertices, mesh.verticesSize, mesh.shader->getBufferLayout());
		m_resourceManager->addIndexBuffer("Index1", mesh.indices, mesh.indicesSize);
		m_resourceManager->getVertexArray("VAO1")->setVertexBuffer(m_resourceManager->getVertexBuffer("VBO1"));
		m_resourceManager->getVertexArray("VAO1")->setIndexBuffer(m_resourceManager->getIndexBuffer("Index1"));
		m_resourceManager->addMaterial("FC_CUBE", mesh.shader, m_resourceManager->getVertexArray("VAO1"));

		glm::mat4 model = glm::mat4(1.0f);

		mesh.shader->uploadData("u_model", (void*)&model);
		mesh.shader->uploadData("u_vp", (void*)&m_camera->getCamera()->getViewProjection());


	}

	void GameLayer::onDetach()
	{
		LOG_INFO("[GAMELAYER][DETACH]");
	}

	void GameLayer::onUpdate(float deltaTime)
	{
		m_camera->onUpdate(deltaTime);
		for (auto& CGO : m_gameObjects)
		{
			CGO->onUpdate(deltaTime);
		}

		for (auto& renderCommand : m_predrawCommands)
		{
			m_renderer->actionCommand(renderCommand.get());
		}

		m_renderer->submit(m_resourceManager->getMaterial("FC_CUBE"));

		for (auto& renderCommand : m_postdrawCommands)
		{
			m_renderer->actionCommand(renderCommand.get());
		}

	}

	void GameLayer::onEvent(Events::Event& e)
	{
		//Send Event to Camera Controller
		m_camera->onEvent(e);
		//Send Event to All Game Objects
		for (auto& CGO : m_gameObjects) CGO->onEvent(e);
	}
}