#pragma once

namespace Engine {

	enum class API
	{
		None = 0,
		OpenGL = 1
	};

	class RenderAPI
	{
	public:

		static API getAPI() { return s_API; }

	private:
		static API s_API;
	};
}