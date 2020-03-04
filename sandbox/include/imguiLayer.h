#pragma once
#include "Headers/layers/layer.h"
#include "Headers/audio/audio.h"
#include "../enginecode/Headers/ImGui/imgui.h"
#include "../enginecode/Headers/ImGui/imgui_impl_glfw_gl3.h"

namespace Engine {
	class ImGUILayer : public Layer {
	public:
		ImGUILayer();

		void onAttach() override; ///< Run on layer stack attach
		void onDetach() override; ///< Run on layer stack removal
		void onUpdate(float deltaTime); ///< Run every frame
		void onEvent(Events::Event& e) {}; ///< Run on an Event

		void createButton(const char* buttonName, std::pair<float, float> size, std::pair<float, float> position, const char*  text, ImVec4 color, int corner);
		void createImageButton(const char* buttonName, std::pair<float, float> size, std::pair<float, float> position, const char* text, int corner, const char* filepath);
		void loadButton(const char* buttonName, std::pair<float, float> size, std::pair<float, float> position, const char*  text, ImVec4 color, int corner);


		struct ImGuiButton {

			ImGuiButton(const char* buttonName, std::pair<float, float> size, std::pair<float, float> position, const char*  text, ImVec4 color, int corner) {
				this->buttonName = buttonName;
				this->size = size;
				this->position = position;
				this->text = text;
				this->color = color;
				this->corner = corner;
			};
			
			const char* buttonName;
			std::pair<float, float> size;
			std::pair<float, float> position;
			const char*  text;
			ImVec4 color;
			int corner;
		};	

		std::vector<ImGuiButton> buttonsToLoad;
	};
}