#pragma once
#include <string>
#include <memory>
#include "systems/resourceManager.h"
#include "renderer/renderer.h"
#include "cameras/cameraController.h"
#include "events/event.h"


namespace Engine
{
	class Layer
	{
	protected:
		std::string m_name;
		std::shared_ptr<ResourceManager> m_resourceManager;
		std::shared_ptr<Renderer> m_renderer;
		std::shared_ptr<CameraController> m_camera;
	public:
		Layer(const std::string& name);
		virtual void onAttach() = 0;
		virtual void onDetach() = 0;
		virtual void onUpdate(float deltaTime) = 0;
		virtual void onEvent(Event& e) = 0;
		inline std::string& getName() { return m_name; }
		inline std::shared_ptr<ResourceManager>& getResources() { return m_resourceManager; }
		inline std::shared_ptr<Renderer>& getRenderer() { return m_renderer; }
		inline std::shared_ptr<CameraController>& getCamera() { return m_camera; }
	};
};