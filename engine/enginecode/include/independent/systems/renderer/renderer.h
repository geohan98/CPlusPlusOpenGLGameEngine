#pragma once


namespace Engine
{
	class Renderer
	{
	public:
		enum class API
		{
			None = 0, OpenGL = 1
		};
	private:
		static API s_API;
	public:
		static API getAPI() { return s_API; }
	};
}
