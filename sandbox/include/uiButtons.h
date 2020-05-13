#pragma once
#include "Headers/layers/layer.h"
#include "Headers/core/gameObject.h"
#include "Headers/components/materialComponent.h"
#include "Headers/components/PositionComponent.h"
#include "Headers/components/velocityComponent.h"
#include "Headers/cameras/cameraController2D.h"
#include "Headers/events/applicationEvents.h"
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

		bool onWindowResize(Events::WindowResize& e);				///< Window Resize Event
		bool onWindowClose(Events::WindowClose& e);					///< Window Close Event
		bool onWindowMoved(Events::WindowMoved& e);					///< Window Move Event
		bool onWindowLostFocus(Events::WindowLostFocus& e);			///< Window Lost Focus Event

		//glm::ivec2 m_windowSize;
		enum anchorPoints { TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT };

		struct button
		{
			std::pair<float, float> size;
			std::pair<float, float> position;
			int texslot;
			float xOffset;
			float yOffset;
			std::string filepath;
			anchorPoints anchorPoint = TOP_LEFT;
		};

		//std::shared_ptr<Window> m_window;
		//inline std::shared_ptr<Systems::ResourceManager>& getResources() { return m_resourceManager; }
		std::pair<float, float> position;
		int i_Height;
		int i_Width;


		void onDetach() override;

		void onEvent(Events::Event& e);

		std::vector<button> buttonstoload;
		void createButton(int anchor, std::pair<float, float> position, std::string filepath, std::pair<float, float> size, int texslot);
		void onAttach() override;
		void onUpdate(float deltaTime);

	};

}