#include "editorImGUILayer.h"
#include "Headers/core/application.h"
#include "Headers/renderer/renderAPI.h"
#include "msgTypes.h"

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
		m_properties = new Engine::SystemProperties;
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

		//Spawn Rate
		ImGui::SliderFloat("Spawn Rate", &m_properties->m_spawnRate, 0.0, 100.0);

		//Lifetime
		static bool randomLifetime;
		ImGui::Checkbox("Random Lifetime", &randomLifetime);
		if (randomLifetime)
		{
			ImGui::PushItemWidth(100.0f);
			ImGui::Text("Start Lifetime");
			ImGui::InputFloat("Min", &m_properties->m_minStartLifetime, 0, 0, 1);
			ImGui::SameLine();
			ImGui::InputFloat("Max", &m_properties->m_maxStartLifetime, 0, 0, 1);
			ImGui::PopItemWidth();
		}
		else
		{
			ImGui::SliderFloat("Lifetime", &m_properties->m_minStartLifetime, 0.0, 10.0);
			m_properties->m_maxStartLifetime = m_properties->m_minStartLifetime;
		}

		//Rotation
		static bool randomRotation;
		ImGui::Checkbox("Random Rotation", &randomRotation);
		if (randomRotation)
		{
			ImGui::SliderFloat("Rotation Min", &m_properties->m_minStartRotation, 0.0, 90.0);
			ImGui::SliderFloat("Rotation Max", &m_properties->m_maxStartRotation, 0.0, 90.0);
		}
		else
		{
			ImGui::SliderFloat("Rotation", &m_properties->m_minStartRotation, 0.0, 90.0);
			m_properties->m_maxStartRotation = m_properties->m_minStartRotation;
		}

		//Scale
		static bool sizeOverLife;
		ImGui::Checkbox("Size Over Life", &sizeOverLife);
		if (sizeOverLife)
		{
			static bool randomStartSize;
			ImGui::Checkbox("Random Start Size", &randomStartSize);
			if (randomStartSize)
			{
				ImGui::InputFloat("Start Size Min", &m_properties->m_minStartScale, 0.1);
				ImGui::InputFloat("Start Size Max", &m_properties->m_maxStartScale, 0.1);
			}
			else
			{
				ImGui::InputFloat("Start Size Min", &m_properties->m_minStartScale, 0.1);
				m_properties->m_maxStartScale = m_properties->m_minStartScale;
			}
			static bool randomEndSize;
			ImGui::Checkbox("Random End Size", &randomEndSize);
			if (randomEndSize)
			{
				ImGui::InputFloat("End Size Min", &m_properties->m_minEndScale, 0.1);
				ImGui::InputFloat("End Size Max", &m_properties->m_maxEndScale, 0.1);
			}
			else
			{
				ImGui::InputFloat("End Size Min", &m_properties->m_minEndScale, 0.1);
				m_properties->m_maxEndScale = m_properties->m_minEndScale;
			}
		}
		else
		{
			ImGui::SliderFloat("Start Size Min", &m_properties->m_minStartScale, 0.0, 1.0);
			m_properties->m_maxStartScale = m_properties->m_minStartScale;
			m_properties->m_minEndScale = m_properties->m_minStartScale;
			m_properties->m_maxEndScale = m_properties->m_minStartScale;
		}

		//Colour
		static bool colourOverLife;
		ImGui::Checkbox("Colour Over Life", &colourOverLife);
		if (colourOverLife)
		{
			static bool randomStartColour;
			ImGui::Checkbox("Random Start Colour", &randomStartColour);
			if (randomStartColour)
			{
				ImGui::ColorEdit4("Start Colour Min", &m_properties->m_minStartColour.r);
				ImGui::ColorEdit4("Start Colour Max", &m_properties->m_maxStartColour.r);
			}
			else
			{
				ImGui::ColorEdit4("Start Colour", &m_properties->m_minStartColour.r);
				m_properties->m_maxStartColour = m_properties->m_minStartColour;
			}
			static bool randomEndColour;
			ImGui::Checkbox("Random End Colour", &randomEndColour);
			if (randomEndColour)
			{
				ImGui::ColorEdit4("End Colour Min", &m_properties->m_minEndColour.r);
				ImGui::ColorEdit4("End Colour Max", &m_properties->m_maxEndColour.r);
			}
			else
			{
				ImGui::ColorEdit4("End Colour", &m_properties->m_minEndColour.r);
				m_properties->m_maxEndColour = m_properties->m_minEndColour;
			}
		}
		else
		{
			ImGui::ColorEdit4("Colour", &m_properties->m_minStartColour.r);
			m_properties->m_maxStartColour = m_properties->m_minStartColour;
			m_properties->m_minEndColour = m_properties->m_minStartColour;
			m_properties->m_maxEndColour = m_properties->m_minStartColour;
		}

		//Linear Velocity
		static bool randomLinearVelocity;
		ImGui::Checkbox("Random Linear Velocity", &randomLinearVelocity);
		if (randomLinearVelocity)
		{
			ImGui::InputFloat3("Linear Velocity Min", &m_properties->m_minStartLinearVelocity.x, 0.1);
			ImGui::InputFloat3("Linear Velocity Max", &m_properties->m_maxStartLinearVelocity.x, 0.1);
		}
		else
		{
			ImGui::InputFloat3("Linear Velocity Min", &m_properties->m_minStartLinearVelocity.x, 0.1);
			m_properties->m_minStartLinearVelocity = m_properties->m_minStartLinearVelocity;
		}

		//Angular Velocity
		static bool randomAngularVelocity;
		ImGui::Checkbox("Random Angular Velocity", &randomAngularVelocity);
		if (randomAngularVelocity)
		{
			ImGui::InputFloat("Angular Velocity Min", &m_properties->m_minStartAngularVelocity, 1.0);
			ImGui::InputFloat("Angular Velocity Max", &m_properties->m_maxStartAngularVelocity, 1.0);
		}
		else
		{
			ImGui::InputFloat("Angular Velocity", &m_properties->m_minStartAngularVelocity, 1.0);
			m_properties->m_maxStartAngularVelocity = m_properties->m_minStartAngularVelocity;
		}

		if (ImGui::Button("Apply"))
		{
			notifySubscribers(UPDATE_PARTICLE_SYSTEM, m_properties);
		}

		ImGui::End();

		static bool b = true;
		ImGui::ShowDemoWindow(&b);

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