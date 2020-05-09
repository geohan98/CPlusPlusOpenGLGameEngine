#pragma once
#include "Headers/layers/layer.h"
#include "Headers/ImGui/imgui.h"
#include "Headers/ImGui/imgui_impl_glfw_gl3.h"
#include "Headers/components/particleComponent.h"

namespace ParticleEditor
{
	class EditorImGuiLayer : public Engine::Layer
	{
	private:
		Engine::ParticleSystemProperties* m_properties; ///< properties of the particle system on the layer
		ImVec2 m_windowSize; ///< Current Size of the window
		char inputTextBuffer[80] = {}; ///< Buffer/ cache for the filepath to save/load to/from
	public:
		EditorImGuiLayer(const std::string& name = "EditorImGuiLayer") : Engine::Layer(name) {}; ///< Constructor
		void onAttach() override; ///< Runs when layer is attached to layer stack
		void onDetach() override; ///< Runs when layer is removed from layer stack
		void onUpdate(float deltaTime); ///< Runs evebry frame
		void onEvent(Engine::Events::Event& e); ///< Runs when an event occours in application
		bool onWindowResize(Engine::Events::WindowResize& e); ///< Runs when an event is a resize event
	public:
		void beNotified(MsgType _type, std::any _data) override {}; ///< par of oberserver pattern
	};
}