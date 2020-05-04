#pragma once
#include "engine_pch.h"
#include "Headers/core/application.h"
#include "Headers/layers/layer.h"
#include <iostream>
#include "Headers/events/applicationEvents.h"
#include <vector>
#include "Headers/core/application.h"
#include "Headers/windows/GLFW_windowSys.h"
#include "Headers/core/gameObject.h"
#include "Headers/components/materialComponent.h"
#include "Headers/components/PositionComponent.h"
#include "Headers/components/velocityComponent.h"
#include "Headers/cameras/cameraController2D.h"
#include "Headers/events/keyEvents.h"
#include "Headers/events/mouseEvents.h"
#include "Headers/systems/log.h"

namespace Engine {
	
	class uiButtons : public Layer {
		
	public:
		uiButtons(const std::string& name = "Ui Layer") : Layer(name) {};
		
		std::vector<std::shared_ptr<GameObject>> m_gameObjects;			///< All the GameObjects
		std::vector<std::shared_ptr<MaterialComponent>> m_materials;	///< All the material Components
		std::vector<std::shared_ptr<PositionComponent>> m_positions;	///< All the position Components
		std::vector<std::shared_ptr<VelocityComponent>> m_velocities;
	
		
		std::shared_ptr<Systems::ResourceManager> m_resourceManager;
		std::shared_ptr<Window> m_window;
		inline std::shared_ptr<Systems::ResourceManager>& getResources() { return m_resourceManager; }
		std::pair<float, float> position;
		enum anchorPoints { TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT };
		int i_Height = m_window->getHeight();
		int i_Width = m_window->getWidth();
		
		void onEvent(Events::Event& e) override {};
		void onDetach() override {};

		void uiButtons::onAttach() {

			m_resourceManager = Engine::Application::getInstance().getRousrceManager();
			m_renderer = std::shared_ptr<Renderer::Renderer>(Renderer::Renderer::createBasic2D());
			m_renderer->actionCommand(Renderer::RenderCommand::setClearColourCommand(0.0, 0.0, 0.0, 1.0f));
			m_renderer->actionCommand(Renderer::RenderCommand::setBlendMode(true));
			m_camera = std::shared_ptr<CameraController2D>(new CameraController2D);
			m_camera->init(0.0f, 1280.0f, 720.0f, 0.0f);
		}

		

		void createButton(int anchor, std::pair<float, float> position, std::string filepath, std::pair<float, float> size) {
			button tempbutton = {};
			m_resourceManager = Engine::Application::getInstance().getRousrceManager();
			m_resourceManager->addTexture(filepath);
			tempbutton.size = size;
			tempbutton.position = position;


			if (anchor == 0) {

				tempbutton.anchorPoint = TOP_LEFT;
				tempbutton.xOffset = position.first;
				tempbutton.yOffset = position.second;
				

			}
			else if (anchor == 1) {

				tempbutton.anchorPoint = TOP_RIGHT;
				tempbutton.xOffset = i_Width - position.first;
				tempbutton.yOffset = position.second;
				

			}

			else if (anchor == 2)
			{

				tempbutton.anchorPoint = BOTTOM_LEFT;
				tempbutton.xOffset = position.first;
				tempbutton.yOffset = i_Height - position.second;

			}

			else if (anchor == 3)
			{

				tempbutton.anchorPoint = BOTTOM_RIGHT;
				tempbutton.xOffset = i_Width - position.first;
				tempbutton.yOffset = i_Height - position.second;

			}
			
			m_materials.push_back(std::shared_ptr<MaterialComponent>(new MaterialComponent(m_resourceManager->getMaterial("TEXT"))));
			m_positions.push_back(std::shared_ptr<PositionComponent>(new PositionComponent(glm::vec3(640.0f, 460.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(100.0f, 100.0f, 100.0f))));
			m_velocities.push_back(std::shared_ptr<VelocityComponent>(new VelocityComponent(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 90.0f))));
			m_gameObjects.push_back(std::shared_ptr<GameObject>(new GameObject));
			m_gameObjects.back()->addComponent(m_materials.back());
			m_gameObjects.back()->addComponent(m_positions.back());
			m_gameObjects.back()->addComponent(m_velocities.back());
			buttonstoload.push_back(tempbutton);
			
		};


		struct button 
		{
			std::pair<float, float> size;
			std::pair<float, float> position;
			float xOffset;
			float yOffset;
			anchorPoints anchorPoint = TOP_LEFT;
		};

		std::vector<button> buttonstoload;

		
		

		void uiButtons::onUpdate(float deltaTime)
		{
			m_camera->onUpdate(deltaTime);
			for (auto& CGO : m_gameObjects)
			{
				CGO->onUpdate(deltaTime);
			}

			m_renderer->actionCommand(Renderer::RenderCommand::setDepthTestLessCommand(false));
			m_renderer->actionCommand(Renderer::RenderCommand::setBackFaceCullingCommand(false));
			m_renderer->actionCommand(Renderer::RenderCommand::ClearDepthColourBufferCommand());

			std::pair<std::string, void*> data("u_vp", (void*)&m_camera->getCamera()->getViewProjection()[0][0]);
			ComponentMessage msg(ComponentMessageType::UniformSet, data);
			m_materials.back()->receiveMessage(msg);


			unsigned int texSlot = 1;
			m_resourceManager->getTexture("assets/textures/buttonTest.png")->bind(texSlot);
			m_materials.back()->getMaterial()->setDataElement("u_texData", (void*)&texSlot);
			glm::mat4 model = glm::mat4(1.0f);
			m_resourceManager->getTexture("assets/textures/buttonTest.png")->bind();
			m_resourceManager->bindFontTexture(texSlot);
			m_renderer->submit(m_materials.back()->getMaterial());

			
			

			for (int i = 0; i < buttonstoload.size(); i++) 
			{

				if (buttonstoload.at(i).anchorPoint == TOP_LEFT) //if current button anchor is top left, then do ...
				{
					buttonstoload.at(i).position.first = buttonstoload.at(i).xOffset;
					buttonstoload.at(i).position.second = buttonstoload.at(i).yOffset;
				}
				else if (buttonstoload.at(i).anchorPoint == TOP_RIGHT) //if current button anchor is top right, then do ...
				{
					buttonstoload.at(i).position.first = i_Width - buttonstoload.at(i).xOffset;
					buttonstoload.at(i).position.second = buttonstoload.at(i).yOffset;
					
				}
				else if (buttonstoload.at(i).anchorPoint == BOTTOM_LEFT) //if current button anchor is bottom left, then do ...
				{
					buttonstoload.at(i).position.first = buttonstoload.at(i).xOffset;
					buttonstoload.at(i).position.second = i_Height - buttonstoload.at(i).yOffset;
				}
				else if (buttonstoload.at(i).anchorPoint == BOTTOM_RIGHT) //if current button anchor is bottom right, then do ...
				{
					buttonstoload.at(i).position.first = i_Width - buttonstoload.at(i).xOffset;
					buttonstoload.at(i).position.second = i_Height - buttonstoload.at(i).yOffset;
				}


				
			}
		}
		
		
	};

};
