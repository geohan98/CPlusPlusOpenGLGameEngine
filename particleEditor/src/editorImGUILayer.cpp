#include "editorImGUILayer.h"
#include "Headers/core/application.h"
#include "Headers/renderer/renderAPI.h"
#include "msgTypes.h"
#include "Headers/core/application.h"
#include "particleFileManager.h"

namespace ParticleEditor
{
	void EditorImGuiLayer::onAttach()
	{

		glm::ivec2 size = Engine::Application::getInstance().getWindowSize();
		m_windowSize.x = size.x;
		m_windowSize.y = size.y;

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
		m_properties = new Engine::ParticleSystemProperties;
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

			if (ImGui::MenuItem("Close")) { Engine::Application::getInstance().close(); }
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("View"))
		{
			if (ImGui::MenuItem("Toggle Fullscreen")) { Engine::Application::getInstance().toggleFullscreen(); }
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();

		ImGuiWindowFlags windowFlags = 0;
		windowFlags |= ImGuiWindowFlags_NoResize;
		windowFlags |= ImGuiWindowFlags_NoCollapse;
		windowFlags |= ImGuiWindowFlags_NoMove;
		ImGui::Begin("Particle Properties", NULL, windowFlags);
		ImVec2 size = m_windowSize;
		size.x = 400.0f;
		size.y = size.y - 50.0f;
		ImVec2 pos = ImVec2(10, 37.5f);
		ImGui::SetWindowPos(pos);
		ImGui::SetWindowSize(size);
		ImGui::PushItemWidth(100.0f);

		//Spawn Rate
		ImGui::Text("Spawn Rate");
		ImGui::InputFloat("", &m_properties->m_spawnRate, 0.1, 1.0, 2);
		ImGui::NewLine();

		//Lifetime
		ImGui::Text("Lifetime");
		static bool randomLifetime;
		if (randomLifetime)
		{
			ImGui::InputFloat("Min Lifetime", &m_properties->m_minStartLifetime, 0.1, 1.0, 1);
			ImGui::SameLine();
			ImGui::InputFloat("Max Lifetime", &m_properties->m_maxStartLifetime, 0.1, 1.0, 1);

		}
		else
		{
			ImGui::InputFloat("Lifetime", &m_properties->m_minStartLifetime, 0.1, 1.0, 1);
			m_properties->m_maxStartLifetime = m_properties->m_minStartLifetime;
		}
		ImGui::Checkbox("Random Lifetime", &randomLifetime);
		ImGui::NewLine();

		//Rotation
		ImGui::Text("Spawn Rotation");
		static bool randomRotation;
		if (randomRotation)
		{
			ImGui::InputFloat("Min Rotation", &m_properties->m_minStartRotation, 1, 10, 1);
			ImGui::SameLine();
			ImGui::InputFloat("Max Rotation", &m_properties->m_maxStartRotation, 1, 10, 1);
		}
		else
		{
			ImGui::InputFloat("Rotation", &m_properties->m_minStartRotation, 1, 10, 1);
			m_properties->m_maxStartRotation = m_properties->m_minStartRotation;
		}
		ImGui::Checkbox("Random Rotation", &randomRotation);
		ImGui::NewLine();

		//Scale
		ImGui::Text("Scale");
		static bool sizeOverLife;
		if (sizeOverLife)
		{
			static bool randomStartSize;
			if (randomStartSize)
			{
				ImGui::Text("Start");
				ImGui::InputFloat("Min Start Scale", &m_properties->m_minStartScale, 0.1, 1.0, 2);
				ImGui::InputFloat("Max Start Scale", &m_properties->m_maxStartScale, 0.1, 1.0, 2);
			}
			else
			{
				ImGui::InputFloat("Start", &m_properties->m_minStartScale, 0.1, 1.0, 2);
				m_properties->m_maxStartScale = m_properties->m_minStartScale;
			}
			ImGui::Checkbox("Random Start Size", &randomStartSize);
			static bool randomEndSize;
			if (randomEndSize)
			{
				ImGui::Text("End");
				ImGui::InputFloat("Min End Scale", &m_properties->m_minEndScale, 0.1, 1.0, 2);
				ImGui::InputFloat("Max End Scale", &m_properties->m_maxEndScale, 0.1, 1.0, 2);
			}
			else
			{
				ImGui::InputFloat("End", &m_properties->m_minEndScale, 0.1, 1.0, 2);
				m_properties->m_maxEndScale = m_properties->m_minEndScale;
			}
			ImGui::Checkbox("Random End Size", &randomEndSize);
		}
		else
		{
			ImGui::InputFloat("Scale", &m_properties->m_minStartScale, 0.1, 1.0, 2);
			m_properties->m_maxStartScale = m_properties->m_minStartScale;
			m_properties->m_minEndScale = m_properties->m_minStartScale;
			m_properties->m_maxEndScale = m_properties->m_minStartScale;
		}
		ImGui::Checkbox("Size Over Life", &sizeOverLife);
		ImGui::NewLine();

		//Colour
		ImGui::PushItemWidth(200.0f);
		ImGui::Text("Colour");
		static bool colourOverLife;
		if (colourOverLife)
		{
			static bool randomStartColour;
			if (randomStartColour)
			{
				ImGui::Text("Start");
				ImGui::ColorEdit4("Min Start", &m_properties->m_minStartColour.r);
				ImGui::ColorEdit4("Max Start", &m_properties->m_maxStartColour.r);
			}
			else
			{
				ImGui::ColorEdit4("Start", &m_properties->m_minStartColour.r);
				m_properties->m_maxStartColour = m_properties->m_minStartColour;
			}
			ImGui::Checkbox("Random Start Colour", &randomStartColour);
			static bool randomEndColour;
			if (randomEndColour)
			{
				ImGui::Text("End");
				ImGui::ColorEdit4("Min End", &m_properties->m_minEndColour.r);
				ImGui::ColorEdit4("Max End", &m_properties->m_maxEndColour.r);
			}
			else
			{
				ImGui::ColorEdit4("End", &m_properties->m_minEndColour.r);
				m_properties->m_maxEndColour = m_properties->m_minEndColour;
			}
			ImGui::Checkbox("Random End Colour", &randomEndColour);
		}
		else
		{
			ImGui::ColorEdit4("", &m_properties->m_minStartColour.r);
			m_properties->m_maxStartColour = m_properties->m_minStartColour;
			m_properties->m_minEndColour = m_properties->m_minStartColour;
			m_properties->m_maxEndColour = m_properties->m_minStartColour;
		}
		ImGui::Checkbox("Colour Over Life", &colourOverLife);
		ImGui::PopItemWidth();
		ImGui::NewLine();

		//Linear Velocity
		ImGui::Text("Linear Velocity");
		static bool randomLinearVelocity;
		if (randomLinearVelocity)
		{
			ImGui::InputFloat3("Linear Min", &m_properties->m_minStartLinearVelocity.x, 1);
			ImGui::InputFloat3("Linear Max", &m_properties->m_maxStartLinearVelocity.x, 1);
		}
		else
		{
			ImGui::InputFloat3("Linear", &m_properties->m_minStartLinearVelocity.x, 0.1);
			m_properties->m_maxStartLinearVelocity = m_properties->m_minStartLinearVelocity;
		}
		ImGui::Checkbox("Random Linear Velocity", &randomLinearVelocity);
		ImGui::NewLine();

		//Angular Velocity
		ImGui::Text("Angular Velocity");
		static bool randomAngularVelocity;
		if (randomAngularVelocity)
		{
			ImGui::InputFloat("Angular Min", &m_properties->m_minStartAngularVelocity, 0.5, 5.0, 2);
			ImGui::InputFloat("Angular Max", &m_properties->m_maxStartAngularVelocity, 0.5, 5.0, 2);
		}
		else
		{
			ImGui::InputFloat("Angular Velocity", &m_properties->m_minStartAngularVelocity, 0.5, 5.0, 2);
			m_properties->m_maxStartAngularVelocity = m_properties->m_minStartAngularVelocity;
		}
		ImGui::Checkbox("Random Angular Velocity", &randomAngularVelocity);
		ImGui::NewLine();

		//Gravity
		ImGui::Checkbox("Gravity", &m_properties->m_gravity);
		//Drag
		ImGui::InputFloat("Drag", &m_properties->m_drag, 0.01, 0.1, 2);

		if (ImGui::Button("Apply"))
		{
			notifySubscribers(UPDATE_PARTICLE_SYSTEM, m_properties);
		}

		ImGui::NewLine();
		ImGui::NewLine();

		ImGui::InputText("Filepath", inputTextBuffer, sizeof(inputTextBuffer));

		if (ImGui::Button("Save")) {
			ParticleEditor::ParticleFileManager::save(m_properties, inputTextBuffer);
		}

		ImGui::SameLine();

		if (ImGui::Button("Load")) {
			m_properties = ParticleEditor::ParticleFileManager::load(inputTextBuffer);
			notifySubscribers(UPDATE_PARTICLE_SYSTEM, m_properties);
		}

		ImGui::PopItemWidth();
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
		Engine::Events::EventDispatcher dispatcher(e);
		dispatcher.dispatch<Engine::Events::WindowResize>(std::bind(&EditorImGuiLayer::onWindowResize, this, std::placeholders::_1));
	}
	bool EditorImGuiLayer::onWindowResize(Engine::Events::WindowResize& e)
	{
		m_windowSize.x = e.getWidth();
		m_windowSize.y = e.getHeight();
		return false;
	}
}