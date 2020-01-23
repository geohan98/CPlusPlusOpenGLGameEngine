#pragma once

#include <fstream>

#include "json.hpp"
#include "../enginecode/Headers/systems/log.h"

namespace Engine
{
	class JSONLoaderLog
	{
	private:
	public:
		static void load(const std::string& filepath)
		{
			std::fstream handle(filepath, std::ios::in);
			if (!handle.is_open()) {

				LOG_CORE_WARN("Could not open level: {0}", filepath);
			}
			nlohmann::json layerJSON;
			handle >> layerJSON;

			LOG_CORE_WARN("Filepaths to resources to be preloaded");
			if (layerJSON.count("Asyncload") > 0)
			{
				std::string asyncLoadStrings[3] = { "shaders", "textures", "fonts" };
				for (int i = 0; i < 3; i++)
				{
					for (auto& filepath : layerJSON["Asyncload"][asyncLoadStrings[i]])
					{
						LOG_CORE_INFO("\t{0} filepath: {1}", asyncLoadStrings[i], filepath["filepath"].get<std::string>());
					}
				}
			}
			else LOG_CORE_INFO("None");

			LOG_CORE_INFO("Array sizes for layer");
			if (layerJSON.count("MemoryInfo") > 0)
			{
				std::string arrayStrings[5] = { "gameObjects", "materials", "position", "velocity", "controllers" };
				for (int i = 0; i < 5; i++)
				{
					LOG_CORE_INFO("\t{0}\t{1}", arrayStrings[i], layerJSON["MemoryInfo"][arrayStrings[i].c_str()].get<int>());
				}
			}
			else LOG_CORE_INFO("None");

			LOG_CORE_INFO("Layer Camera Settings");
			if (layerJSON.count("camera") > 0)
			{
				std::string type = layerJSON["camera"]["type"].get<std::string>();
				if (type.compare("Euler3D") == 0)
				{
					float fov = layerJSON["camera"]["fov"].get<float>();
					float aspectRatio = layerJSON["camera"]["aspectRatio"].get<float>();
					float nearClip = layerJSON["camera"]["nearClip"].get<float>();
					float farClip = layerJSON["camera"]["farClip"].get<float>();
					LOG_CORE_INFO("\tEuler3D camera: FOV {0}, aspect ratio {1}, near clip plane {2}, far clip plane {3}", fov, aspectRatio, nearClip, farClip);
				}
				else if (type.compare("FixedOrtho2D") == 0)
				{
					float top = layerJSON["camera"]["top"].get<float>();
					float left = layerJSON["camera"]["left"].get<float>();
					float width = layerJSON["camera"]["width"].get<float>();
					float height = layerJSON["camera"]["height"].get<float>();
					LOG_CORE_INFO("\tFixed Orthographic 2D camera: top {0}, left {1}, width {2}, height {3}", top, left, width, height);
				}
			}

			LOG_CORE_INFO("Renderer Settings");
			if (layerJSON.count("renderer") > 0)
			{
				std::string type = layerJSON["renderer"]["type"].get<std::string>();
				LOG_CORE_INFO("\tRenderer type: {0}", type);
			}

			LOG_CORE_INFO("Game Objects");
			if (layerJSON.count("GameObjects") > 0)
			{
				for (auto& object : layerJSON["GameObjects"])
				{
					LOG_CORE_INFO("{0}", object["name"].get<std::string>());
					if (object.count("material") > 0) {
						LOG_CORE_INFO("Material Component");
						if (object["material"].count("model") > 0)
						{
							LOG_CORE_INFO("\tVAO: {0}", object["material"]["model"].get<std::string>());
							LOG_CORE_INFO("\tshader: {0}", object["material"]["shader"].get<std::string>());
						}
						else if (object["material"].count("text") > 0)
						{
							LOG_CORE_INFO("\tText: {0}", object["material"]["text"].get<std::string>());
							LOG_CORE_INFO("\tFont: {0}", object["material"]["font"].get<std::string>());
							LOG_CORE_INFO("\tChar Size: {0}", object["material"]["charSize"].get<int>());
							float r = object["material"]["colour"]["r"].get<float>();
							float g = object["material"]["colour"]["g"].get<float>();
							float b = object["material"]["colour"]["b"].get<float>();
							LOG_CORE_INFO("\tFont colour({0}, {1}, {2})", r, g, b);
						}
					}
					if (object.count("position") > 0) {
						LOG_CORE_INFO("Position Component");
						LOG_CORE_INFO("\tTrans: ({0}, {1}, {2})", object["position"]["trans"]["x"].get<float>(), object["position"]["trans"]["y"].get<float>(), object["position"]["trans"]["z"].get<float>());
						LOG_CORE_INFO("\tRot: ({0}, {1}, {2})", object["position"]["rot"]["x"].get<float>(), object["position"]["rot"]["y"].get<float>(), object["position"]["rot"]["z"].get<float>());
						LOG_CORE_INFO("\tScale: ({0}, {1}, {2})", object["position"]["scale"]["x"].get<float>(), object["position"]["scale"]["y"].get<float>(), object["position"]["scale"]["z"].get<float>());
					}
					if (object.count("velocity") > 0) {
						LOG_CORE_INFO("Velocity Component");
						LOG_CORE_INFO("\tLinear: ({0}, {1}, {2})", object["velocity"]["linear"]["x"].get<float>(), object["velocity"]["linear"]["y"].get<float>(), object["velocity"]["linear"]["z"].get<float>());
						LOG_CORE_INFO("\tAngular: ({0}, {1}, {2})", object["velocity"]["angular"]["x"].get<float>(), object["velocity"]["angular"]["y"].get<float>(), object["velocity"]["angular"]["z"].get<float>());
					}
					if (object.count("oscillate") > 0) {
						LOG_CORE_INFO("Oscillate Component");
						LOG_CORE_INFO("\tState: {0}", object["oscillate"]["state"].get<std::string>());
						LOG_CORE_INFO("\tTime: {0}", object["oscillate"]["time"].get<float>());
					}
					if (object.count("keyCtrl") > 0) LOG_CORE_INFO("Keyboard controller Component");
				}
			}
			else LOG_CORE_INFO("None");

			LOG_CORE_INFO("Uniform Buffer Objects");
			if (layerJSON.count("UBOs") > 0)
			{
				for (auto& object : layerJSON["UBOs"])
				{
					if (object.count("name") > 0) LOG_CORE_INFO("name: {0}", object["name"].get<std::string>());
					if (object.count("layout") > 0)
					{
						LOG_CORE_INFO("Layout: {");
						for (auto& object2 : object["layout"])
						{
							LOG_CORE_INFO("{0}, ", object2);
						}
						LOG_CORE_INFO("}");
					}
					if (object.count("shaders") > 0)
					{
						LOG_CORE_INFO("Is bound to shader blocks:");
						for (auto& object2 : object["shaders"])
						{
							if (object2.count("filepath") > 0 && object2.count("block") > 0)
								LOG_CORE_INFO("\t{0} block {1}", object2["filepath"].get<std::string>(), object2["block"].get<std::string>());
						}
					}
					if (object.count("data") > 0)
					{
						LOG_CORE_INFO("Data:");
						for (auto& object2 : object["data"])
						{
							auto& type = object2["type"];
							if (type == "pointer")
							{
								if (object2["var"].get<std::string>().compare("CAM_VIEW") == 0) LOG_CORE_INFO("Camera View matrix");
								else if (object2["var"].get<std::string>().compare("CAM_PROJ") == 0) LOG_CORE_INFO("Camera Projection matrix");
								else LOG_CORE_INFO("Unknown pointer");
							}
							if (type == "Float3") LOG_CORE_INFO("\tFloat3: ({0}, {1}, {2})", object2["x"].get<float>(), object2["y"].get<float>(), object2["z"].get<float>());
						}
					}
				}
			}

			LOG_CORE_INFO("Render Commands");
			if (layerJSON.count("RendererCommands") > 0)
			{
				std::string stages[4] = { "init", "predraw", "postdraw", "exit" };
				for (int i = 0; i < 4; i++)
				{
					if (layerJSON["RendererCommands"].count(stages[i]) > 0)
					{
						LOG_CORE_INFO("Render commands at {0} stage:", stages[i]);
						for (auto& object : layerJSON["RendererCommands"][stages[i]])
						{
							std::string type = object["type"].get<std::string>();

							if (type.compare("ClearDepthColourBuffer") == 0)
							{
								LOG_CORE_INFO("ClearDepthColourBuffer()");
							}

							if (type.compare("SetClearColour") == 0)
							{
								float r = object["r"].get<float>();
								float g = object["g"].get<float>();
								float b = object["b"].get<float>();
								float a = object["a"].get<float>();
								LOG_CORE_INFO("SetClearColour({0}, {1}, {2}, {3})", r, g, b, a);
							}

							if (type.compare("SetDepthTestLess") == 0)
							{
								bool enabled = object["enabled"].get<bool>();
								LOG_CORE_INFO("SetDepthTestLess({0})", enabled);
							}

							if (type.compare("SetBackfaceCulling") == 0)
							{
								bool enabled = object["enabled"].get<bool>();
								LOG_CORE_INFO("SetBackfaceCulling({0})", enabled);
							}

							if (type.compare("SetOneMinusAlphaBlending") == 0)
							{
								bool enabled = object["enabled"].get<bool>();
								LOG_CORE_INFO("SetOneMinusAlphaBlending({0})", enabled);
							}
						}
					}
				}
			}
		}
	};
}