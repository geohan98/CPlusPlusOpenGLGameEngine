#include "engine_pch.h"

#include "..\include\imguiLayer.h"

#include "../enginecode/Headers/ImGui/imgui.h"
#include "../enginecode/Headers/ImGui/imgui_impl_glfw_gl3.h"
#include "Headers/windows/window.h"
#include "Headers/windows/GLFW_windowImp.h"
#include "../enginecode/Headers/core/application.h"

namespace Engine {

	ImGUILayer::ImGUILayer() : Layer("ImGUI Layer")
	{

	}

	ImGUILayer::~ImGUILayer()
	{

	}

	void ImGUILayer::onAttach()
	{
		// audio stuff, abstract to its own layer
		//Audio audioEngine;
		//audioEngine.Init();

		//audioEngine.LoadBank("../assets/audio/master.bank", FMOD_STUDIO_LOAD_BANK_NORMAL);
		//audioEngine.LoadBank("../assets/audio/master.strings.bank", FMOD_STUDIO_LOAD_BANK_NORMAL);
		//audioEngine.LoadEvent("event:/oofEvent");
		
		//audioEngine.LoadSound("../assets/audio/oof.mp3", false);
		//audioEngine.PlayEvent("event:/oofEvent");
		
		

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
		// audio stuff, abstract to its own layer
		//audioEngine.Update();
		//audioEngine.PlaySounds("../assets/audio/oof.mp3", { 0,0,0 }, 0.2f);

		ImGui_ImplGlfwGL3_NewFrame();

		ImGui::ShowDemoWindow();

		ImGui::Render();
		ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGUILayer::onEvent(Events::Event & e)
	{

	}
}
