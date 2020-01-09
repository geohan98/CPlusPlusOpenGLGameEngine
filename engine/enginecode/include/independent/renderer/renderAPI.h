#pragma once

namespace Engine {

	/**
	 *  RenderAPI
	 */
	class RenderAPI
	{
	public:
		enum class API
		{
			None = 0,
			OpenGL = 1
		};
		static API getAPI() { return s_API; } ///<Return the Render API

	private:
		static API s_API; ///< API in USE
	};
}