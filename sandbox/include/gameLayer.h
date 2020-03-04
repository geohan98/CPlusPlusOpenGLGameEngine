#pragma once
#include "../enginecode/Headers/layers/layer.h"
#include "../enginecode/Headers/core/gameObject.h"
#include "../enginecode/Headers/components/materialComponent.h"
#include "../enginecode/Headers/components/PositionComponent.h"
#include "../enginecode/Headers/components/velocityComponent.h"
#include "../enginecode/Headers/events/applicationEvents.h"
#include "../enginecode/Headers/events/keyEvents.h"
#include "../enginecode/Headers/events/mouseEvents.h"
#include "../enginecode/Headers/renderer/uniformBuffer.h"



namespace Engine
{
	/**
	 *  Game Layer, Handles Game objects
	 */
	class GameLayer : public Layer
	{
	private:
		std::vector<std::shared_ptr<GameObject>> m_gameObjects;			///< All the GameObjects
		std::vector<std::shared_ptr<MaterialComponent>> m_materials;	///< All the material Components
		std::vector<std::shared_ptr<PositionComponent>> m_positions;	///< All the position Components
		std::vector<std::shared_ptr<VelocityComponent>> m_velocities;	///< All the velocity Components
		std::shared_ptr<Renderer::UniformBuffer> m_uniformBuffer;
		Renderer::SceneData m_sceneData;
		//Application Events
		bool onWindowResize(Events::WindowResize& e);				///< Window Resize Event
		bool onWindowClose(Events::WindowClose& e);					///< Window Close Event
		bool onWindowMoved(Events::WindowMoved& e);					///< Window Move Event
		bool onWindowLostFocus(Events::WindowLostFocus& e);			///< Window Lost Focus Event
		//Key Events
		bool onKeyPressed(Events::KeyPressed& e);					///< Key Press Event
		bool onKeyReleased(Events::KeyReleased& e);					///< Key Release Event
		bool onKeyTyped(Events::KeyTyped& e);						///< Key Type Event
		//Mouse Events
		bool onMouseMove(Events::MouseMoved& e);					///< Mouse Move Event
		bool onMouseScrolled(Events::MouseScrolled& e);				///< Mouse Scrolled Event
		bool onMouseButtonPressed(Events::MouseButtonPressed& e);	///< Mouse Button Press Event
		bool onMouseButtonReleased(Events::MouseButtonReleased& e);	///< Mouse Button Release Event
	public:
		GameLayer(const std::string& name = "Game Layer") : Layer(name) {}; ///< Constructor
		void onAttach() override;							///< Run on layer Attach
		void onDetach() override;							///< Run on Layer remove from layer stack
		void onUpdate(float deltaTime) override;			///< Run every Frame
		void onEvent(Events::Event& e) override;					///< Run on an Event
	};
}