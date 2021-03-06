#pragma once
#include "Headers/layers/layer.h"
#include <memory>
#include <string>
#include <vector>
#include "Headers/core/gameObject.h"
#include "Headers/components/materialComponent.h"
#include "Headers/components/PositionComponent.h"
#include "Headers/components/velocityComponent.h"
#include "Headers/events/keyEvents.h"
#include "Headers/events/applicationEvents.h"
#include "Headers/events/mouseEvents.h"

namespace Engine
{
	class GameObject;
	class MaterialComponent;
	class PositionComponent;
	class VelocityComponent;
	class Renderer::RenderCommand;

	/**
	 *  JSON Layer, Create Game objects From a JSON File
	 */
	class JSONLayer : public Layer
	{
	protected:
		std::vector<std::shared_ptr<GameObject>> m_gameObjects;			///< List Of All Game objects
		std::vector<std::shared_ptr<Components::MaterialComponent>> m_materials;	///< List of all Material Components
		std::vector<std::shared_ptr<Components::PositionComponent>> m_positions;	///< List of all Position Components
		std::vector<std::shared_ptr<Components::
			VelocityComponent>> m_velocities;	///< List of all Velocity Components

		std::vector<std::shared_ptr<Renderer::RenderCommand>> m_initCommands;		///< List of all Init Render Commands
		std::vector<std::shared_ptr<Renderer::RenderCommand>> m_predrawCommands;	///< List of all PreDraw Render Commands
		std::vector<std::shared_ptr<Renderer::RenderCommand>> m_postdrawCommands;	///< List of all PostDraw Render Commands
		std::vector<std::shared_ptr<Renderer::RenderCommand>> m_exitCommands;		///< List of all Exit Render Commands

		Renderer::SceneData m_sceneData; ///< Uniform Scene Data
		std::list<void*> m_data; ///< Lits of void pointer data
		std::string m_filepath; ///< Filepath of Level File

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
		JSONLayer(const std::string& filepath, const std::string& name = "Layer") : Layer(name), m_filepath(filepath) {} ///< Constructor

		virtual void onAttach() override; ///< Run on layer stack attach
		virtual void onDetach() override; ///< Run on layer stack removal
		virtual void onUpdate(float deltaTime) override; ///< Run every frame
		virtual void onEvent(Events::Event& e) override; ///< Run on an Event

		inline std::vector<std::shared_ptr<GameObject>>& getGameObjects() { return m_gameObjects; }					///< Return all the game objects
		inline std::vector<std::shared_ptr<Components::MaterialComponent>>& getMaterials() { return m_materials; }				///< Return all the material components
		inline std::vector<std::shared_ptr<Components::PositionComponent>>& getPositions() { return m_positions; }				///< Return all the position components
		inline std::vector<std::shared_ptr<Components::VelocityComponent>>& getVelocities() { return m_velocities; }			///< Return all the velocity components

		inline std::vector<std::shared_ptr<Renderer::RenderCommand>>& getInitCommands() { return m_initCommands; }			///< Return all the Init Render Commands
		inline std::vector<std::shared_ptr<Renderer::RenderCommand>>& getPredrawCommands() { return m_predrawCommands; }		///< Return all the	PreDraw Render Commands
		inline std::vector<std::shared_ptr<Renderer::RenderCommand>>& getPostdrawCommands() { return m_postdrawCommands; }	///< Return all the	PostDraw Render Commands
		inline std::vector<std::shared_ptr<Renderer::RenderCommand>>& getExitCommands() { return m_exitCommands; }			///< Return all the	Exit Render Commands

		inline std::list<void*>& getData() { return m_data; }  ///< Return the List of void pointer data
	};
}