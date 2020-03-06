#pragma once
#include "Headers/layers/layer.h"
#include "Headers/audio/audio.h"
#include "../enginecode/Headers/ImGui/imgui.h"
#include "../enginecode/Headers/ImGui/imgui_impl_glfw_gl3.h"

#include "Headers/renderer/texture.h"

namespace Engine {
	class ImGUILayer : public Layer {
	public:
		ImGUILayer();

		std::shared_ptr<Renderer::Texture> texturePtr;

		void onAttach() override; ///< Run on layer stack attach
		void onDetach() override; ///< Run on layer stack removal
		void onUpdate(float deltaTime); ///< Run every frame
		void onEvent(Events::Event& e) {}; ///< Run on an Event

		void createButton(const char* buttonName, std::pair<float, float> size, std::pair<float, float> position, const char*  text, ImVec4 color, int corner);
		void createImageButton(const char* buttonName, std::pair<float, float> size, std::pair<float, float> position, const char* text, int corner, const char* filepath);
		void loadImageButton(const char* buttonName, std::pair<float, float> size, std::pair<float, float> position, const char* text, int corner, unsigned int textureID);
		void loadButton(const char* buttonName, std::pair<float, float> size, std::pair<float, float> position, const char*  text, ImVec4 color, int corner);
		//void loadImage(const char* imageName, ...)

		struct ImGuiImageButton {
			ImGuiImageButton(const char* buttonName, std::pair<float, float> size, std::pair<float, float> position, const char* text, int corner, unsigned int textureID)
				: buttonName(buttonName), size(size), position(position), text(text), corner(corner), textureID(textureID) {
			};

			const char* buttonName;
			std::pair<float, float> size;
			std::pair<float, float> position;
			const char* text;
			int corner;
			unsigned int textureID;

		};

		struct ImGuiButton {

			ImGuiButton(const char* buttonName, std::pair<float, float> size, std::pair<float, float> position, const char*  text, ImVec4 color, int corner)
			: buttonName(buttonName), size(size), position(position), text(text), color(color), corner(corner) {
			};
			
			const char* buttonName;
			std::pair<float, float> size;
			std::pair<float, float> position;
			const char*  text;
			ImVec4 color;
			int corner;
		};	

		std::vector<ImGuiButton> buttonsToLoad;
		std::vector<ImGuiImageButton> imageButtonsToLoad;
	};
}