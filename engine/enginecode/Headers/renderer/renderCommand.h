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
			bool destroyOnAction;																				///< Should it be destroyed
			static RenderCommand* ClearDepthColourBufferCommand(bool destroy = true);								///< Clear the depth and color buffer
			static RenderCommand* setClearColourCommand(float r, float g, float b, float a, bool destroy = true);	///< Set Window Clear color 
			static RenderCommand* setDepthTestLessCommand(bool enabled, bool destroy = true);						///< Set if depth dest should run
			static RenderCommand* setBackFaceCullingCommand(bool enabled, bool destroy = true);						///< Set if back face culling should run
			static RenderCommand* setPolygonModeFill(bool destroy = true);											///< Set Render Mode to Fill
			static RenderCommand* setPolygonModeLine(bool destroy = true);											///< Set Render Mode to Wire frame
			static RenderCommand* setPolygonModePoint(bool destroy = true);											///< Set Render Mode to Vertexes
			static RenderCommand* setBlendMode(bool enbaled, bool destroy = true);									///< Set if blending should happen
			static RenderCommand* setLineWidth(float width, bool destroy = true);									///< Set if blending should happen
		};
	}
}