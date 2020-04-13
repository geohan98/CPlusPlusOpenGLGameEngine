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
		Engine::SystemProperties* m_properties;
	public:
		EditorImGuiLayer(const std::string& name = "EditorImGuiLayer") : Engine::Layer(name) {};
		void onAttach() override;
		void onDetach() override;
		void onUpdate(float deltaTime);
		void onEvent(Engine::Events::Event& e);
	public:
		void beNotified(MsgType _type, std::any _data) override
		{

		};
	};
}