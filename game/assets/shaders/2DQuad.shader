#region Vertex
#version 440 core

layout(location = 0) in vec2 a_vertexPosition;
layout(location = 1) in vec2 a_texCoord;

out vec2 texCoord;


uniform mat4 u_model;
uniform mat4 u_vp;


void main()
{
	texCoord = a_texCoord;
	gl_Position = u_vp * u_model * vec4(a_vertexPosition, 0.0f, 1.0f);
}

#region Fragment
#version 440 core

layout(location = 0) out vec4 colour;
in vec2 texCoord;
uniform sampler2D u_texData;
void main()
{
	colour = texture(u_texData, texCoord);
}