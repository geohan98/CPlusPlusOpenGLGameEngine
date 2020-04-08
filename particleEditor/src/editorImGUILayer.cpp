#include "editorImGUILayer.h"
#include "Headers/core/application.h"
#include "Headers/renderer/renderAPI.h"

namespace ParticleEditor
{
	void EditorImGuiLayer::onAttach()
	{
		ImGui::CreateContext();

		ImGui::StyleColorsDark();

		if (Engine::Renderer::RenderAPI::getAPI() == Engine::Renderer::RenderAPI::API::OpenGL)
		{
			ImGui_ImplGlfwGL3_Init(static_cast<GLFWwindow*>(Engine::Application::getInstance().getWindow()->getNativeWindow()), true);
		}
		else
		{
			LOG_CRITICAL("[PARTICLE EDITOR][UI LAYER][UI LAYER ONLY SUPPORTS OPENGL]");
		}

		ImGuiIO& io = ImGui::GetIO();
		ImFont* roboto = io.Fonts->AddFontFromFileTTF("../sandbox/assets/fonts/Roboto-Medium.ttf", 16.0f);
	}
	void EditorImGuiLayer::onDetach()
	{
		ImGui_ImplGlfwGL3_Shutdown();
		ImGui::DestroyContext();
	}
	void EditorImGuiLayer::onUpdate(float deltaTime)
	{
		ImGui_ImplGlfwGL3_NewFrame();

		//Main Menu Bar
		ImGui::BeginMainMenuBar();
		if (ImGui::BeginMenu("Particle Editor"))
		{
			if (ImGui::MenuItem("New")) {}
			if (ImGui::MenuItem("Save")) {}
			if (ImGui::MenuItem("Save As")) {}
			ImGui::Separator();
			if (ImGui::MenuItem("Close")) { Engine::Application::getInstance().close(); }
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("View"))
		{
			if (ImGui::MenuItem("Toggle Fullscreen")) { Engine::Application::getInstance().toggleFullscreen(); }
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();

		ImGui::Begin("Particle Properties");
		if (ImGui::TreeNode("Spawn"))
		{
			ImGui::Text("Spawn Rate");
			ImGui::TreePop();
		}
		ImGui::End();

		ImGui::SetNextWindowBgAlpha(1.0f);
		ImGui::Render();

		if (Engine::Renderer::RenderAPI::getAPI() == Engine::Renderer::RenderAPI::API::OpenGL)
		{
			ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
		}
	}
	void EditorImGuiLayer::onEvent(Engine::Events::Event& e)
	{
	}
}