#pragma once

#include "Headers/layers/layer.h"
#include "Headers/renderer/renderer.h"
#include "Headers/renderer/model.h"
#include "Headers/cameras/cameraController3D.h"

namespace Engine
{
	class MeshLayer : public Layer
	{
	private:
		std::shared_ptr<Renderer::Renderer> m_renderer;
		std::shared_ptr<CameraController> m_camera;
		Model lettercube;
	public:
		MeshLayer(const std::string& name = "Game Layer") : Layer(name) {};
		~MeshLayer() {};
		void onAttach() override;
		void onDetach() override;
		void onUpdate(float deltaTime) override;
		void onEvent(Events::Event& e) override;
	};
}