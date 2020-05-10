#include "engine_pch.h"
#include "meshLayer.h"
#include "Headers/core/application.h"

namespace Engine
{
#pragma region Attach & Detach

	void MeshLayer::onAttach()
	{
		m_renderer = std::shared_ptr<Renderer::Renderer>(Renderer::Renderer::createBasic3D());
		m_camera = std::shared_ptr<CameraController3D>(new CameraController3D);
		m_camera->init(80.0f, 1280.0f / 720.0f, 0.1, 100.0f);

		//lettercube = Model("assets/propane/Propane_LOD3.obj");

		m_renderer->actionCommand(Renderer::RenderCommand::setDepthTestLessCommand(true));
		m_renderer->actionCommand(Renderer::RenderCommand::setBlendMode(true));
		m_renderer->actionCommand(Renderer::RenderCommand::setBackFaceCullingCommand(true));
		m_renderer->actionCommand(Renderer::RenderCommand::setClearColourCommand(1.0f, 1.0f, 0.0f, 1.0f));
		//m_renderer->actionCommand(Renderer::RenderCommand::setPolygonModeLine(true));

		gam = std::shared_ptr<GameObject>(new GameObject);
		pos = std::shared_ptr<PositionComponent>(new PositionComponent(glm::vec3(0.f, 0.f, -5.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.1f, 0.1f, 0.1f)));
		//mat = std::shared_ptr<MaterialComponent>(new MaterialComponent(lettercube.getMaterials()[0]));
		mod = std::shared_ptr<Components::ModelComponent>(new Components::ModelComponent("assets/propane/Propane_LOD3.obj"));
		phy = std::shared_ptr<PhysicsComponent>(new PhysicsComponent);
		phy->setup(glm::vec3(0.f, 0.f, -60.f), glm::vec4(0.f, 0.f, 0.f, 0.f), glm::vec3(0.5f, 0.5f, 0.5f), 2.5f);

		gam->addComponent(pos);
		//gam->addComponent(mat);
		gam->addComponent(phy);
		gam->addComponent(mod);



	}
	void MeshLayer::onDetach()
	{
	}

#pragma endregion

#pragma region Update & Event

	void MeshLayer::onUpdate(float deltaTime)
	{
		m_camera->onUpdate(deltaTime);
		m_renderer->actionCommand(Renderer::RenderCommand::ClearDepthColourBufferCommand(true));

		gam->onUpdate(deltaTime);


		mod->setDataElement("u_vp", (void*)& m_camera->getCamera()->getViewProjection());
		for each (auto matt in mod->getMaterials())
		{
			m_renderer->submit(matt);
		}





	}
	void MeshLayer::onEvent(Events::Event& e)
	{

	}

#pragma endregion
}