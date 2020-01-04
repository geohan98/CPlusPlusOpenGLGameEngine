#pragma once
#include "components/component.h"
#include "fileLoaders/textLoader.h"

namespace Engine
{
	class MeshComponent : public Component
	{
	private:
		std::shared_ptr<TextModel> m_mesh;
	public:
		MeshComponent(std::string& filepath)
		{
			m_mesh = std::shared_ptr<TextModel>(new TextModel);
		}
	};
}