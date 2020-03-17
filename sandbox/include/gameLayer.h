#pragma once
#include "Headers/layers/layer.h"
#include "Headers/core/gameObject.h"
#include "Headers/components/PositionComponent.h"
#include "Headers/components/PhysicsComponent.h"
#include "Headers/components/materialComponent.h"

#include"Headers/renderer/material.h"
#include"Headers/renderer/vertexArray.h"
#include"Headers/renderer/vertexBuffer.h"
#include"Headers/renderer/indexBuffer.h"
#include"Headers/renderer/shader.h"

namespace Engine
{
	/**
	 *  Game Layer, Handles Game objects
	 */
	class GameLayer : public Layer
	{
	private:
		std::vector<std::shared_ptr<GameObject>> m_gameObjects;					///< All the GameObjects
		std::vector<std::shared_ptr<PositionComponent>> m_positionComponents;
		std::vector<std::shared_ptr<MaterialComponent>> m_materials;				///< All the material Components
		std::vector<std::shared_ptr<PhysicsComponent>> m_physicsComponent;

		std::vector<std::shared_ptr<Renderer::RenderCommand>> m_predrawCommands;	///< List of all PreDraw Render Commands
		std::vector<std::shared_ptr<Renderer::RenderCommand>> m_postdrawCommands;	///< List of all PostDraw Render Commands






		std::shared_ptr<Renderer::Material> MAT;
		std::shared_ptr<Renderer::VertexArray> VAO;
		std::shared_ptr<Renderer::VertexBuffer> VBO;
		std::shared_ptr<Renderer::IndexBuffer> IBO;
		std::shared_ptr<Renderer::Shader> SHADER;
	public:
		GameLayer(const std::string& name = "Game Layer") : Layer(name) {};		///< Constructor
		void onAttach() override;												///< Run on layer Attach
		void onDetach() override;												///< Run on Layer remove from layer stack
		void onUpdate(float deltaTime) override;								///< Run every Frame
		void onEvent(Events::Event& e) override;								///< Run on an Event
	};
}