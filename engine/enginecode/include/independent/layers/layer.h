#pragma once
#include <string>
#include <memory>
#include "systems/resourceManager.h"
#include "renderer/renderer.h"
#include "cameras/cameraController.h"
#include "events/event.h"


namespace Engine
{
	/**
	 *  Layer, Handles Resource Manager, Renderer, and Camera controller
	 */
	class Layer
	{
	protected:
		std::string m_name; ///< Layer Name
		std::shared_ptr<Systems::ResourceManager> m_resourceManager; ///< Pointer to resource manager
		std::shared_ptr<Renderer::Renderer> m_renderer; ///< Pointer to renderer
		std::shared_ptr<CameraController> m_camera; ///< Pointer to camera controller
	public:
		Layer(const std::string& name); ///< Constructor
		virtual void onAttach() = 0; ///< Run on layer stack attach
		virtual void onDetach() = 0; ///< Run on layer stack remove
		virtual void onUpdate(float deltaTime) = 0; ///< Run every frame
		virtual void onEvent(Events::Event& e) = 0; ///< Run on an Event
		inline std::string& getName() { return m_name; } ///< Return the layer name
		inline std::shared_ptr<Systems::ResourceManager>& getResources() { return m_resourceManager; } ///< Return the resource manager
		inline std::shared_ptr<Renderer::Renderer>& getRenderer() { return m_renderer; } ///< Return the renderer
		inline std::shared_ptr<CameraController>& getCamera() { return m_camera; } ///< Return the Camera controller
	};
};