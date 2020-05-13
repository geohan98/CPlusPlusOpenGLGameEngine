#include "engine_pch.h"
#include "Headers/systems/log.h"
#include "particleLayer.h"
#include "editorCameraController.h"

namespace ParticleEditor
{
	void ParticleLayer::onAttach()
	{
		//Initalisation
		m_resourceManager = std::shared_ptr<Engine::Systems::ResourceManager>(new Engine::Systems::ResourceManager());
		m_renderer = std::shared_ptr<Engine::Renderer::Renderer>(Engine::Renderer::Renderer::createBasic3D());
		m_camera = std::shared_ptr<Engine::CameraController>(new EditorCameraController());
		//FOV, ASPECT RATIO, NEAR, FAR
		m_camera->init(90.0f, 1280.0f / 720.0f, 0.1f, 100.0f);
		//PredrawCommands
		m_predrawCommands.push_back(std::shared_ptr <Engine::Renderer::RenderCommand>(Engine::Renderer::RenderCommand::setBlendMode(true, false)));
		m_predrawCommands.push_back(std::shared_ptr <Engine::Renderer::RenderCommand>(Engine::Renderer::RenderCommand::setBackFaceCullingCommand(true, false)));
		m_predrawCommands.push_back(std::shared_ptr <Engine::Renderer::RenderCommand>(Engine::Renderer::RenderCommand::setDepthTestLessCommand(true, false)));
		m_predrawCommands.push_back(std::shared_ptr <Engine::Renderer::RenderCommand>(Engine::Renderer::RenderCommand::setClearColourCommand(0.1f, 0.1f, 0.1f, 1.0f, false)));
		m_predrawCommands.push_back(std::shared_ptr <Engine::Renderer::RenderCommand>(Engine::Renderer::RenderCommand::ClearDepthColourBufferCommand(false)));
		m_predrawCommands.push_back(std::shared_ptr <Engine::Renderer::RenderCommand>(Engine::Renderer::RenderCommand::setPolygonModeFill(false)));
		m_predrawCommands.push_back(std::shared_ptr <Engine::Renderer::RenderCommand>(Engine::Renderer::RenderCommand::setLineWidth(2.0f, false)));
		//Uniform Buffer
		Engine::Renderer::UniformBufferLayout viewProjectionLayout = { Engine::Renderer::ShaderDataType::Mat4,Engine::Renderer::ShaderDataType::Mat4, };
		std::shared_ptr<Engine::Renderer::UniformBuffer> viewProjectionBuffer = std::shared_ptr<Engine::Renderer::UniformBuffer>(Engine::Renderer::UniformBuffer::create(viewProjectionLayout.getStride(), viewProjectionLayout));
		//Scene Data
		std::vector<void*> viewProjectionData(2);
		viewProjectionData[0] = (void*)&m_camera->getCamera()->getProjection();
		viewProjectionData[1] = (void*)&m_camera->getCamera()->getView();
		m_sceneData[viewProjectionBuffer] = viewProjectionData;
		//World Grid
		m_worldGrid = std::shared_ptr<WorldGrid>(new WorldGrid());
		//Particle Emiter
		m_gameObject = std::shared_ptr<Engine::GameObject>(new Engine::GameObject());
		m_positionComponent = std::shared_ptr<Engine::PositionComponent>(new Engine::PositionComponent(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)));
		m_gameObject->addComponent(m_positionComponent);
		m_particleComponent = std::shared_ptr<Engine::Components::ParticleComponent>(new Engine::Components::ParticleComponent(10.0f, 0.1f));
		m_gameObject->addComponent(m_particleComponent);
		viewProjectionBuffer->attachShaderBlock(m_particleComponent->getMaterial()->getShader(), "VP");
	}

	void ParticleLayer::onDetach()
	{
	}

	void ParticleLayer::onUpdate(float deltaTime)
	{
		m_camera->onUpdate(deltaTime);
		m_gameObject->onUpdate(deltaTime);
		//PreDraw Commands
		for (auto& renderCommand : m_predrawCommands)
		{
			m_renderer->actionCommand(renderCommand.get());
		}
		//Begin Scene
		m_renderer->beginScene(m_sceneData);
		//Draw Grid
		glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, 0.0));
		m_worldGrid->getMaterial()->setDataElement("u_model", &model[0][0]);
		m_worldGrid->getMaterial()->setDataElement("u_vp", (void*)&m_camera->getCamera()->getViewProjection());
		m_renderer->submit(m_worldGrid->getMaterial(), Engine::Renderer::RendererDrawType::Lines);
		//Draw Particle System
		m_renderer->submit(m_particleComponent->getMaterial(), Engine::Renderer::RendererDrawType::Point);
		//PostDraw Commands
		for (auto& renderCommand : m_postdrawCommands)
		{
			m_renderer->actionCommand(renderCommand.get());
		}
	}

	void ParticleLayer::onEvent(Engine::Events::Event& e)
	{
		m_camera->onEvent(e);
	}
}
