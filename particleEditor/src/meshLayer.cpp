#include "engine_pch.h"
#include "meshLayer.h"
#include "Headers/ASSIMPLoaderLog.h"


namespace Engine
{
#pragma region Attach & Detach

	void MeshLayer::onAttach()
	{
		m_renderer = std::shared_ptr<Renderer::Renderer>(Renderer::Renderer::createBasic3D());
		m_camera = std::shared_ptr<CameraController3D>(new CameraController3D);
		m_camera->init(80.0f, 1280.0f / 720.0f, 0.1, 100.0f);
		lettercube = Model("assets/propane/Propane_LOD3.obj");

		m_renderer->actionCommand(Renderer::RenderCommand::setDepthTestLessCommand(true));
		m_renderer->actionCommand(Renderer::RenderCommand::setBlendMode(true));
		//m_renderer->actionCommand(Renderer::RenderCommand::setBackFaceCullingCommand(true));
		m_renderer->actionCommand(Renderer::RenderCommand::setPolygonModeLine(true));

		gam = std::shared_ptr<GameObject>(new GameObject);
		pos = std::shared_ptr<PositionComponent>(new PositionComponent(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.f, 1.f, 1.f)));
		mat = std::shared_ptr<MaterialComponent>(new MaterialComponent(lettercube.getMaterials()[0]));
		phy = std::shared_ptr<PhysicsComponent>(new PhysicsComponent);
		phy->setup(glm::vec3(0.f, 0.f, 0.f), glm::vec4(0.f, 0.f, 0.f, 0.f), glm::vec3(0.5f, 0.5f, 0.5f), 2.5f);

		gam->addComponent(pos);
		gam->addComponent(mat);
		gam->addComponent(phy);

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

		glm::mat4 model = glm::scale(glm::mat4(1.0), glm::vec3(0.1, 0.1, 0.1));
		for (unsigned int i = 0; i < lettercube.getNumMaterials(); i++)
		{
			lettercube.getMaterials()[i]->getShader()->uploadData("u_vp", (void*)& m_camera->getCamera()->getViewProjection());
			//lettercube.getMaterials()[i]->getShader()->uploadData("u_model", &model[0][0]);

			m_renderer->submit(lettercube.getMaterials()[i]);
		}
	}
	void MeshLayer::onEvent(Events::Event& e)
	{
	}

#pragma endregion
}