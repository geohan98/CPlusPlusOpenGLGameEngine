#include "engine_pch.h"
#include "meshLayer.h"
#include "Headers/core/application.h"
#include "Headers/cameras/cameraController3D.h"

namespace Engine
{
#pragma region Attach & Detach

	void MeshLayer::onAttach()
	{
		//Renderer
		m_renderer = std::shared_ptr<Renderer::Renderer>(Renderer::Renderer::createBasic3D());
		//Resource Manager
		m_resourceManager = Application::getInstance().getResourceManager();
		//Camera
		m_camera = std::shared_ptr<CameraController3D>(new CameraController3D);
		m_camera->init(80.0f, 1280.0f / 720.0f, 0.1, 100.0f);
		m_camera->setPosition(glm::vec3(0.0, -1.5, -5.0));
		//World Grid
		m_worldGrid = std::shared_ptr<WorldGrid>(new WorldGrid());
		//PredrawCommands
		m_predrawCommands.push_back(std::shared_ptr <Engine::Renderer::RenderCommand>(Engine::Renderer::RenderCommand::setBlendMode(true, false)));
		m_predrawCommands.push_back(std::shared_ptr <Engine::Renderer::RenderCommand>(Engine::Renderer::RenderCommand::setBackFaceCullingCommand(true, false)));
		m_predrawCommands.push_back(std::shared_ptr <Engine::Renderer::RenderCommand>(Engine::Renderer::RenderCommand::setDepthTestLessCommand(true, false)));
		m_predrawCommands.push_back(std::shared_ptr <Engine::Renderer::RenderCommand>(Engine::Renderer::RenderCommand::setClearColourCommand(0.1f, 0.1f, 0.1f, 1.0f, false)));
		m_predrawCommands.push_back(std::shared_ptr <Engine::Renderer::RenderCommand>(Engine::Renderer::RenderCommand::ClearDepthColourBufferCommand(false)));
		m_predrawCommands.push_back(std::shared_ptr <Engine::Renderer::RenderCommand>(Engine::Renderer::RenderCommand::setPolygonModeFill(false)));
		m_predrawCommands.push_back(std::shared_ptr <Engine::Renderer::RenderCommand>(Engine::Renderer::RenderCommand::setLineWidth(2.0f, false)));

		m_cube = std::shared_ptr<GameObject>(new GameObject());
		m_cubePositionComponent = std::shared_ptr<Components::PositionComponent>(new Components::PositionComponent(glm::vec3(0.0, 2.0, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 1.0, 1.0)));
		m_cubeModelComponent = std::shared_ptr<Components::ModelComponent>(new Components::ModelComponent("assets/models/cube_1x1.obj"));
		m_cubePhysicsBoxComponent = std::shared_ptr<Components::PhysicsBoxComponent>(new Components::PhysicsBoxComponent(glm::vec3(0.0, 2.0, 0.0), glm::vec4(0.0, 0.0, 0.0, 0.0), glm::vec3(0.5, 0.5, 0.5), 1.0f, true));
		m_cube->addComponent(m_cubePositionComponent);
		m_cube->addComponent(m_cubeModelComponent);
		m_cube->addComponent(m_cubePhysicsBoxComponent);
		m_cubePhysicsBoxComponent->setLinearVelocity(glm::vec3(0, 2.0, 0));

		m_plane = std::shared_ptr<GameObject>(new GameObject());
		m_planePositionComponent = std::shared_ptr<Components::PositionComponent>(new Components::PositionComponent(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(5.0, 0.1, 5.0)));
		m_planeModelComponent = std::shared_ptr<Components::ModelComponent>(new Components::ModelComponent("assets/models/cube_1x1.obj"));
		m_planePhysicsBoxComponent = std::shared_ptr<Components::PhysicsBoxComponent>(new Components::PhysicsBoxComponent(glm::vec3(0.0, 0.0, 0.0), glm::vec4(0.0, 0.0, 0.0, 0.0), glm::vec3(5.0, 0.05, 5.0), 1.0f, false));
		m_plane->addComponent(m_planePositionComponent);
		m_plane->addComponent(m_planeModelComponent);
		m_plane->addComponent(m_planePhysicsBoxComponent);
	}
	void MeshLayer::onDetach()
	{

	}

#pragma endregion

#pragma region Update & Event

	void MeshLayer::onUpdate(float deltaTime)
	{
		//Update Camera
		m_camera->onUpdate(deltaTime);
		//Update GameObjects
		m_cube->onUpdate(deltaTime);
		m_plane->onUpdate(deltaTime);
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
		//Cube
		m_cubeModelComponent->setDataElement("u_vp", (void*)&m_camera->getCamera()->getViewProjection());
		for each (auto mat in m_cubeModelComponent->getMaterials())
		{
			m_renderer->submit(mat);
		}
		//Plane
		m_planeModelComponent->setDataElement("u_vp", (void*)&m_camera->getCamera()->getViewProjection());
		for each (auto mat in m_planeModelComponent->getMaterials())
		{
			m_renderer->submit(mat);
		}
		//PostDraw Commands
		for (auto& renderCommand : m_postdrawCommands)
		{
			m_renderer->actionCommand(renderCommand.get());
		}
	}
	void MeshLayer::onEvent(Events::Event& e)
	{
		m_camera->onEvent(e);
	}

#pragma endregion
}