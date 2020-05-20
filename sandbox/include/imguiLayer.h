#pragma once
#include "Headers/layers/layer.h"
#include "Headers/audio/audio.h"
#include "Headers/ImGui/imgui.h"
#include "Headers/ImGui/imgui_impl_glfw_gl3.h"
#include "Headers/renderer/texture.h"

namespace Engine {

	/**
	 *  ImGUI Layer, Handles creation, loading and event handling of ImGUI buttons
	 */
	class ImGUILayer : public Layer {
	public:
		ImGUILayer(); ///< Constructor

		void onAttach() override; ///< Run on layer stack attach
		void onDetach() override; ///< Run on layer stack removal
		void onUpdate(float deltaTime); ///< Run every frame
		void onEvent(Events::Event& e) {}; ///< Run on an Event

		void helloWorld(); ///< Test function to pass to a button click

		void createButton(const char* buttonName, std::pair<float, float> size, std::pair<float, float> position, const char* text, ImVec4 color, int corner, std::function<void()> func); ///< Takes multiple parameters and uses them to create an ImGUI button
		void loadButton(const char* buttonName, std::pair<float, float> size, std::pair<float, float> position, const char* text, ImVec4 color, int corner, std::function<void()> func); ///< Loads a button already in the buttonsToLoad vector to the screen

		struct ImGuiButton {  ///< Holds all the information about the ImGui button
			ImGuiButton(const char* buttonName, std::pair<float, float> size, std::pair<float, float> position, const char* text, ImVec4 color, int corner, std::function<void()> func)
				: buttonName(buttonName), size(size), position(position), text(text), color(color), corner(corner), functionHolder(func) {
			};

			const char* buttonName;
			std::pair<float, float> size;
			std::pair<float, float> position;
			const char* text;
			ImVec4 color;
			int corner;
			std::function<void()> functionHolder;
		};

		std::vector<ImGuiButton> buttonsToLoad; ///< Stores buttons that need to be rendered every frame to the screen
	};
}