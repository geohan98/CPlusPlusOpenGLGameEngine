#pragma once
#include "layers/layer.h"
#include <memory>
#include <string>
#include <vector>

#include "core/gameObject.h"
#include "components/materialComponent.h"
#include "components/PositionComponent.h"
#include "components/velocityComponent.h"

namespace Engine
{
	class GameObject;
	class MaterialComponent;
	class PositionComponent;
	class VelocityComponent;
	class RenderCommand;

	/**
	 *  JSON Layer, Create Game objects From a JSON File
	 */
	class JSONLayer : public Layer
	{
	protected:
		std::vector<std::shared_ptr<GameObject>> m_gameObjects;			///< List Of All Game objects
		std::vector<std::shared_ptr<MaterialComponent>> m_materials;	///< List of all Material Components
		std::vector<std::shared_ptr<PositionComponent>> m_positions;	///< List of all Position Components
		std::vector<std::shared_ptr<VelocityComponent>> m_velocities;	///< List of all Velocity Components

		std::vector<std::shared_ptr<RenderCommand>> m_initCommands;		///< List of all Init Render Commands
		std::vector<std::shared_ptr<RenderCommand>> m_predrawCommands;	///< List of all PreDraw Render Commands
		std::vector<std::shared_ptr<RenderCommand>> m_postdrawCommands;	///< List of all PostDraw Render Commands
		std::vector<std::shared_ptr<RenderCommand>> m_exitCommands;		///< List of all Exit Render Commands

		SceneData m_sceneData; ///< Uniform Scene Data
		std::list<void*> m_data; ///< Lits of void pointer data
		std::string m_filepath; ///< Filepath of Level File
	public:
		JSONLayer(const std::string& filepath, const std::string& name = "Layer") : Layer(name), m_filepath(filepath) {} ///< Constructor

		virtual void onAttach() override; ///< Run on layer stack attach
		virtual void onDetach() override; ///< Run on layer stack removal
		virtual void onUpdate(float deltaTime) override; ///< Run every frame
		virtual void onEvent(Event& e) override; ///< Ru on an Event

		inline std::vector<std::shared_ptr<GameObject>>& getGameObjects() { return m_gameObjects; }					///< Return all the game objects
		inline std::vector<std::shared_ptr<MaterialComponent>>& getMaterials() { return m_materials; }				///< Return all the material components
		inline std::vector<std::shared_ptr<PositionComponent>>& getPositions() { return m_positions; }				///< Return all the position components
		inline std::vector<std::shared_ptr<VelocityComponent>>& getVelocities() { return m_velocities; }			///< Return all the velocity components

		inline std::vector<std::shared_ptr<RenderCommand>>& getInitCommands() { return m_initCommands; }			///< Return all the Init Render Commands
		inline std::vector<std::shared_ptr<RenderCommand>>& getPredrawCommands() { return m_predrawCommands; }		///< Return all the	PreDraw Render Commands
		inline std::vector<std::shared_ptr<RenderCommand>>& getPostdrawCommands() { return m_postdrawCommands; }	///< Return all the	PostDraw Render Commands
		inline std::vector<std::shared_ptr<RenderCommand>>& getExitCommands() { return m_exitCommands; }			///< Return all the	Exit Render Commands

		inline std::list<void*>& getData() { return m_data; }  ///< Return the List of void pointer data
	};
}