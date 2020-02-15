#include "engine_pch.h"

#include "..\include\imguiLayer.h"

#include "../enginecode/Headers/ImGui/imgui.h"
#include "../enginecode/Headers/ImGui/imgui_impl_glfw_gl3.h"
#include "Headers/windows/window.h"
#include "Headers/windows/GLFW_windowImp.h"
#include "../enginecode/Headers/core/application.h"

namespace Engine {

	ImGUILayer::ImGUILayer() : Layer("ImGUI Layer") {};

	void ImGUILayer::onAttach()
	{	
		ImGui::CreateContext();
		
		ImGui::StyleColorsDark();

		ImGui_ImplGlfwGL3_Init(static_cast<GLFWwindow*>(Application::getInstance().getWindow()->getNativeWindow()), true);
	}

	void ImGUILayer::onDetach()
	{
		ImGui_ImplGlfwGL3_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGUILayer::onUpdate(float deltaTime)
	{
		ImGui_ImplGlfwGL3_NewFrame();

		ImGui::ShowDemoWindow();

		ImGui::Render();
		ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
	}
}
