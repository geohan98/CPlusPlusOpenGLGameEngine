

namespace Engine {

	class RenderAPI
	{
	public:
		enum class API
		{
			None = 0,
			OpenGL = 1
		};
		static API getAPI() { return s_API; }

	private:
		static API s_API;
	};
}