#pragma once


namespace Engine
{
	namespace Renderer {
		/**
		 *  Render Commands
		 */
		class RenderCommand
		{
		public:
			virtual void action() = 0;																				///< Run the render command
			bool dontDestroyOnAction;																				///< Should it be destroyed
			static RenderCommand* ClearDepthColourBufferCommand(bool destroy = false);								///< Clear the depth and color buffer
			static RenderCommand* setClearColourCommand(float r, float g, float b, float a, bool destroy = false);	///< Set Window Clear color 
			static RenderCommand* setDepthTestLessCommand(bool enabled, bool destroy = false);						///< Set if depth dest should run
			static RenderCommand* setBackFaceCullingCommand(bool enabled, bool destroy = false);						///< Set if back face culling should run
			static RenderCommand* setPolygonModeFill(bool destroy = false);											///< Set Render Mode to Fill
			static RenderCommand* setPolygonModeLine(bool destroy = false);											///< Set Render Mode to Wire frame
			static RenderCommand* setPolygonModePoint(bool destroy = false);											///< Set Render Mode to Vertexes
			static RenderCommand* setBlendMode(bool enbaled, bool destroy = false);									///< Set if blending should happen
		};
	}
}