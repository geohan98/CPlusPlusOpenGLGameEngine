#include "engine_pch.h"
#include "Headers/systems/log.h"
#include "particleLayer.h"
#include "Headers/cameras/cameraController3D.h"

namespace ParticleDesigner
{
	void ParticleLayer::onAttach()
	{
		//Initalization
		m_resourceManager = std::shared_ptr<Engine::Systems::ResourceManager>(new Engine::Systems::ResourceManager());
		m_renderer = std::shared_ptr<Engine::Renderer::Renderer>(Engine::Renderer::Renderer::createBasic3D());
		m_camera = std::shared_ptr<Engine::CameraController>(new Engine::CameraController3D());
		//FOV, ASPECT RATIO, NEAR, FAR
		m_camera->init(90.0f, 1280.0f / 720.0f, 0.1f, 100.0f);
		//PredrawCommands
		m_predrawCommands.push_back(std::shared_ptr < Engine::Renderer::RenderCommand >(Engine::Renderer::RenderCommand::setBlendMode(false, false)));
		m_predrawCommands.push_back(std::shared_ptr < Engine::Renderer::RenderCommand >(Engine::Renderer::RenderCommand::setBackFaceCullingCommand(true, false)));
		m_predrawCommands.push_back(std::shared_ptr < Engine::Renderer::RenderCommand >(Engine::Renderer::RenderCommand::setDepthTestLessCommand(true, false)));
		m_predrawCommands.push_back(std::shared_ptr < Engine::Renderer::RenderCommand >(Engine::Renderer::RenderCommand::setClearColourCommand(0.1f, 0.1f, 0.1f, 1.0f, false)));
		m_predrawCommands.push_back(std::shared_ptr < Engine::Renderer::RenderCommand >(Engine::Renderer::RenderCommand::ClearDepthColourBufferCommand(false)));
		m_predrawCommands.push_back(std::shared_ptr < Engine::Renderer::RenderCommand >(Engine::Renderer::RenderCommand::setPolygonModeFill(false)));
		m_predrawCommands.push_back(std::shared_ptr < Engine::Renderer::RenderCommand >(Engine::Renderer::RenderCommand::setLineWidth(2.0f, false)));
		//World Grid
		m_worldGrid = std::shared_ptr<WorldGrid>(new WorldGrid());
		//Debug Cube
		m_debugCube = std::shared_ptr<Engine::Model>(new Engine::Model("assets/models/DebugCube.obj"));
	}

	void ParticleLayer::onDetach()
	{
	}

	void ParticleLayer::onUpdate(float deltaTime)
	{
		m_camera->onUpdate(deltaTime);
		//PreDraw Commands
		for (auto& renderCommand : m_predrawCommands)
		{
			m_renderer->actionCommand(renderCommand.get());
		}
		//Draw Grid
		glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, 0.0));
		m_worldGrid->getMaterial()->setDataElement("u_model", &model[0][0]);
		m_worldGrid->getMaterial()->setDataElement("u_vp", (void*)&m_camera->getCamera()->getViewProjection());
		m_renderer->submit(m_worldGrid->getMaterial(), Engine::Renderer::RendererDrawType::Lines);
		//Draw Debug Cube
		m_renderer->actionCommand(Engine::Renderer::RenderCommand::setPolygonModeLine(true));
		m_debugCube->getMaterials()[0]->setDataElement("u_model", &model[0][0]);
		m_debugCube->getMaterials()[0]->setDataElement("u_vp", (void*)&m_camera->getCamera()->getViewProjection());
		m_renderer->submit(m_debugCube->getMaterials()[0]);
		//PostDraw Commands
		for (auto& renderCommand : m_postdrawCommands)
		{
			m_renderer->actionCommand(renderCommand.get());
		}
	}

	void ParticleLayer::onEvent(Engine::Events::Event& e)
	{
	}
}
