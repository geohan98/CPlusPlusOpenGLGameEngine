#include "engine_pch.h"
#include "systems/log.h"
#include "core/layer2D.h"
#include "cameras/cameraController2D.h"

namespace Engine
{

	void Layer2D::onAttach()
	{
		m_resourceManager = std::shared_ptr<ResourceManager>(new ResourceManager());
		m_resourceManager->start();
		m_renderer = std::shared_ptr<Renderer>(Renderer::createBasic2D());
		m_renderer->actionCommand(RenderCommand::setClearColourCommand(0.9, 0.9, 0.9, 1.0f));
		m_renderer->actionCommand(RenderCommand::setBlendMode(true));
		m_camera = std::shared_ptr<CameraController2D>(new CameraController2D);
		m_camera->init(0.0f, 800.0f, 600.0f, 0.0f);


		float verts[4 * 4] =
		{
			0.0f, 0.0f, 0.0f, 1.0f,
			0.0f, 150.0f, 0.0f, 0.0f,
			150.0f, 150.0f, 1.0f, 0.0f,
			150.0f, 0.0f, 1.0f, 1.0f
		};

		unsigned int indices[4] = { 0,1,2,3 };

		m_resourceManager->addShader("assets/shaders/2DQuad.shader");
		m_resourceManager->addVertexArray("TEXT");
		m_resourceManager->addVertexBuffer("TEXT", verts, sizeof(verts), m_resourceManager->getShader("assets/shaders/2DQuad.shader")->getBufferLayout());
		m_resourceManager->addIndexBuffer("TEXT", indices, 4);
		m_resourceManager->getVertexArray("TEXT")->setVertexBuffer(m_resourceManager->getVertexBuffer("TEXT"));
		m_resourceManager->getVertexArray("TEXT")->setIndexBuffer(m_resourceManager->getIndexBuffer("TEXT"));
		m_resourceManager->addTexture("assets/textures/face.png");
		m_resourceManager->addMaterial("TEXT", m_resourceManager->getShader("assets/shaders/2DQuad.shader"), m_resourceManager->getVertexArray("TEXT"));
	}

	void Layer2D::onDetach()
	{

	}

	void Layer2D::onUpdate(float timestep)
	{
		m_camera->onUpdate(timestep);

		glm::mat4 model = glm::mat4(1.0f);
		m_resourceManager->getMaterial("TEXT")->setDataElement("u_model", (void*)&model[0][0]);
		m_resourceManager->getMaterial("TEXT")->setDataElement("u_vp", (void*)&m_camera->getCamera()->getViewProjection()[0][0]);
		unsigned int texSlot = 0;
		m_resourceManager->getMaterial("TEXT")->setDataElement("u_texData", (void*)&texSlot);

		m_resourceManager->getTexture("assets/textures/face.png")->bind();
		m_renderer->submit(m_resourceManager->getMaterial("TEXT"));
	}

	void Layer2D::onEvent(Event& e)
	{
		m_camera->onEvent(e);
	}

}