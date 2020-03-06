#include "engine_pch.h"

#include "..\include\imguiLayer.h"

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

		

		ImGuiIO& io = ImGui::GetIO();
		ImFont* roboto = io.Fonts->AddFontFromFileTTF("../sandbox/assets/fonts/Roboto-Medium.ttf", 16.0f);

		// Can call createButton from anywhere in the project and it will be added to the buttons to load each frame
		createButton("1", { 100, 50 }, { 100, 100 }, "pos(100,100) button", ImVec4(0.8f, 0.4f, 1.0f, 1.0f), -1);
		createButton("2", { 200, 50 }, { 0, 0 }, "Top right corner button", ImVec4(0.8f, 0.4f, 0.5f, 1.0f), 1);
		createButton("3s", { 200, 100 }, { 0, 0 }, "Bottom left corner button", ImVec4(0.5f, 0.5f, 0.2f, 1.0f), 2);
		createImageButton("3", { 100, 100 }, { 0, 0 }, "Bottom left corner button", 3, "../sandbox/assets/textures/buttonShiny.png");
		createImageButton("10", { 100, 100 }, { 0, 0 }, "Top left corner button", 0, "../sandbox/assets/textures/buttonShiny.png");
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
				buttonsToLoad[i].text, buttonsToLoad[i].color, buttonsToLoad[i].corner);
		}

		for (int i = 0; i < imageButtonsToLoad.size(); i++) {
			loadImageButton(imageButtonsToLoad[i].buttonName, imageButtonsToLoad[i].size, imageButtonsToLoad[i].position, imageButtonsToLoad[i].text, imageButtonsToLoad[i].corner, imageButtonsToLoad[i].textureID);
		}
		
		
		/*if (lives == 3) {
			loadImage(the texture of three lives);
		}*/

		ImGui::SetNextWindowBgAlpha(1.0f); // Make the ImGUI Debug backgrounds fully visible whilst allowing the button backgrounds to be hidden
		ImGui::Render();
		ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGUILayer::createButton(const char* buttonName, std::pair<float, float> size, std::pair<float, float> position, const char* text, ImVec4 color, int corner)
	{
		ImGuiButton button(buttonName, size, position, text, color, corner);
		buttonsToLoad.push_back(button);
	}

	void ImGUILayer::loadButton(const char * buttonName, std::pair<float, float> size, std::pair<float, float> position, const char * text, ImVec4 color, int corner)
	{
		ImGuiIO& io = ImGui::GetIO();

		ImGui::SetNextWindowBgAlpha(0.0f); // Transparent background

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

			ImGui::Button(text, { size.first, size.second });

			ImGui::PopStyleColor(3);
			ImGui::PopID();
		}

		ImGui::End();
	}

	void ImGUILayer::createImageButton(const char* buttonName, std::pair<float, float> size, std::pair<float, float> position, const char* text, int corner, const char* filepath) {
		texturePtr = std::shared_ptr<Renderer::Texture>(Renderer::Texture::createFromFile("../sandbox/assets/textures/buttonShiny.png"));
		unsigned int texID = texturePtr->getId();

		ImGuiImageButton imageButton(buttonName, size, position, text, corner, texID);
		imageButtonsToLoad.push_back(imageButton);
	}

	void ImGUILayer::loadImageButton(const char* buttonName, std::pair<float, float> size, std::pair<float, float> position, const char* text, int corner, unsigned int textureID) {
		ImGuiIO& io = ImGui::GetIO();

		ImGui::SetNextWindowBgAlpha(0.0f); // Transparent background

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

		
		float texWidth = (float)texturePtr->getWidth();
		float texHeight = (float)texturePtr->getHeight();

		if (ImGui::Begin(buttonName, false, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav))
		{
			ImGui::PushID(1);
			
			ImGui::ImageButton((void*)textureID, ImVec2(size.first, size.second), { 0,0 }, { 1,1 }, -1);

			ImGui::PopID();
		}

		ImGui::End();
	}
}
