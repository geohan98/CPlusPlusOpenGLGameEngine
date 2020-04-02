#pragma once

#include "Headers/layers/layer.h"
#include "Headers/renderer/renderer.h"
#include "Headers/renderer/model.h"
#include "Headers/renderer/texture.h"
#include "Headers/cameras/cameraController3D.h"
#include "Headers/components/PhysicsComponent.h"
#include "Headers/components/materialComponent.h"
#include "Headers/components/PositionComponent.h"
#include "Headers/core/gameObject.h"

namespace Engine
{
	class MeshLayer : public Layer
	{
	private:
		std::shared_ptr<Renderer::Renderer> m_renderer;
		std::shared_ptr<CameraController> m_camera;
		Model lettercube;
		std::shared_ptr<Renderer::Texture> texPic;

		std::shared_ptr<PhysicsComponent> phy;
		std::shared_ptr<MaterialComponent> mat;
		std::shared_ptr<PositionComponent> pos;
		std::shared_ptr<GameObject> gam;

	public:
		MeshLayer(const std::string& name = "Game Layer") : Layer(name) {};
		~MeshLayer() {};
		void onAttach() override;
		void onDetach() override;
		void onUpdate(float deltaTime) override;
		void onEvent(Events::Event& e) override;
	};
}