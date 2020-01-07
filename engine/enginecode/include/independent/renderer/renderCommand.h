#pragma once


namespace Engine
{
	class RenderCommand
	{
	public:
		virtual void action() = 0;
		bool dontDestroyOnAction;
		static RenderCommand* ClearDepthColourBufferCommand(bool destroy = true);
		static RenderCommand* setClearColourCommand(float r, float g, float b, float a, bool destroy = true);
		static RenderCommand* setDepthTestLessCommand(bool enabled, bool destroy = true);
		static RenderCommand* setBackFaceCullingCommand(bool enabled, bool destroy = true);
		static RenderCommand* setPolygonModeFill(bool destroy = true);
		static RenderCommand* setPolygonModeLine(bool destroy = true);
		static RenderCommand* setPolygonModePoint(bool destroy = true);
		static RenderCommand* setBlendMode(bool enbaled, bool destroy = true);
	};
}