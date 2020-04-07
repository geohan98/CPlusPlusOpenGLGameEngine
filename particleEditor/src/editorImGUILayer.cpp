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

		//Stuff Here
		ImGui::Begin("Properties");
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

		//Spawn Rate
		static float spawnRate;
		ImGui::SliderFloat("Spawn Rate", &spawnRate, 0.0f, 100.0f);
		//Rotation
		static bool rotationOverLife;
		static float rotMinStart;
		static float rotMaxStart;
		static float rotMinEnd;
		static float rotMaxEnd;
		ImGui::Checkbox("Rotation Over Life", &rotationOverLife);
		if (rotationOverLife)
		{
			static bool randomStart;
			ImGui::Checkbox("Random Start", &randomStart);
			if (randomStart)
			{
				ImGui::SliderFloat("Start Min Rot", &rotMinStart, 0.0f, 90.0f);
				ImGui::SliderFloat("Start Max Rot", &rotMaxStart, 0.0f, 90.0f);
			}
			else
			{
				ImGui::SliderFloat("Start Rot", &rotMinStart, 0.0f, 90.0f);
				rotMaxStart = rotMinStart;
			}

			static bool randomEnd;
			ImGui::Checkbox("Random End", &randomEnd);
			if (randomEnd)
			{
				ImGui::SliderFloat("End Min Rot", &rotMinEnd, 0.0f, 90.0f);
				ImGui::SliderFloat("End Max Rot", &rotMaxEnd, 0.0f, 90.0f);
			}
			else
			{
				ImGui::SliderFloat("End Rot", &rotMinEnd, 0.0f, 90.0f);
				rotMaxEnd = rotMinEnd;
			}
		}
		else
		{
			ImGui::SliderFloat("Start Rot", &rotMinStart, 0.0f, 90.0f);
			rotMaxStart = rotMinStart;
			rotMinEnd = rotMinStart;
			rotMaxEnd = rotMinStart;
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