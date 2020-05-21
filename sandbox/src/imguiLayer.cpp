#include "engine_pch.h"

#include "imguiLayer.h"

#include "Headers/windows/window.h"
#include "Headers/windows/GLFW_windowImp.h"
#include "Headers/core/application.h"

namespace Engine {

	ImGUILayer::ImGUILayer() : Layer("ImGUI Layer") {};

	void ImGUILayer::onAttach()
	{
		ImGui::CreateContext();

		ImGui::StyleColorsDark();

		ImGui_ImplGlfwGL3_Init(static_cast<GLFWwindow*>(Application::getInstance().getWindow()->getNativeWindow()), true);

		ImGuiIO& io = ImGui::GetIO();
		ImFont* roboto = io.Fonts->AddFontFromFileTTF("../sandbox/assets/fonts/Roboto-Medium.ttf", 16.0f);

		// Can call createButton from anywhere in the project and it will be added to the buttons to load each frame
		createButton("AddForce", { 200, 50 }, { 0, 0 }, "Add Force UP Cube", ImVec4(0.8f, 0.4f, 0.5f, 1.0f), 0, [this] { notifySubscribers(0, glm::vec3(0, 1000, 0)); });
		createButton("PlaySound", { 200, 50 }, { 0, 0 }, "Play Sound", ImVec4(0.8f, 0.4f, 0.5f, 1.0f), 1, [this] { Systems::Audio::playSound("assets/audio/woo.mp3"); });
		createButton("ResetObjects", { 200, 50 }, { 0, 0 }, "Reset Objects", ImVec4(0.8f, 0.4f, 0.5f, 1.0f), 2, [this] { notifySubscribers(1, nullptr); });
	}

	void ImGUILayer::onDetach()
	{
		ImGui_ImplGlfwGL3_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGUILayer::onUpdate(float deltaTime)
	{
		ImGui_ImplGlfwGL3_NewFrame();

		for (int i = 0; i < buttonsToLoad.size(); i++) {

			loadButton(buttonsToLoad[i].buttonName, buttonsToLoad[i].size, buttonsToLoad[i].position,
				buttonsToLoad[i].text, buttonsToLoad[i].color, buttonsToLoad[i].corner, buttonsToLoad[i].functionHolder);
		}

		ImGui::SetNextWindowBgAlpha(1.0f);
		ImGui::Render();
		ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGUILayer::helloWorld()
	{
		std::cout << "Button clicked from inside imguilayer" << std::endl;
	}

	void ImGUILayer::createButton(const char* buttonName, std::pair<float, float> size, std::pair<float, float> position, const char* text, ImVec4 color, int corner, std::function<void()> func)
	{
		ImGuiButton button(buttonName, size, position, text, color, corner, func);
		buttonsToLoad.push_back(button);
	}

	void ImGUILayer::loadButton(const char* buttonName, std::pair<float, float> size, std::pair<float, float> position, const char* text, ImVec4 color, int corner, std::function<void()> func)
	{
		ImGuiIO& io = ImGui::GetIO();

		ImGui::SetNextWindowBgAlpha(0.0f);

		const float DISTANCE = 10.0f;
		if (corner != -1)
		{
			ImVec2 window_pos = ImVec2((corner & 1) ? io.DisplaySize.x - DISTANCE : DISTANCE, (corner & 2) ? io.DisplaySize.y - DISTANCE : DISTANCE);
			ImVec2 window_pos_pivot = ImVec2((corner & 1) ? 1.0f : 0.0f, (corner & 2) ? 1.0f : 0.0f);
			ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
		}
		else {
			ImGui::SetNextWindowPos({ position.first, position.second });
		}

		ImGuiStyle& style = ImGui::GetStyle();
		style.WindowBorderSize = 0.0f;

		if (ImGui::Begin(buttonName, false, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav))
		{

			ImGui::PushID(1);

			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(color.x, color.y, color.z, color.w));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(color.x, color.y + 0.1f, color.z, color.w));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(color.x, color.y + 0.2f, color.z, color.w));

			if (ImGui::Button(text, { size.first, size.second })) {
				func();
			}

			ImGui::PopStyleColor(3);
			ImGui::PopID();
		}

		ImGui::End();
	}
}
