#region Vertex
#version 440 core

layout(location = 0) in vec3 a_vertexPosition;
layout(location = 1) in vec2 a_UV;

out vec2 UV;

uniform mat4 u_model;
uniform mat4 u_vp;


void main()
{
	UV = a_UV;
	gl_Position = u_vp * u_model * vec4(a_vertexPosition, 1);
}

#region Fragment
#version 440 core

layout(location = 0) out vec4 colour;

in vec2 UV;

uniform sampler2D u_texData;

void main()
{
	colour = vec4(texture(u_texData, UV).rgb, 1.0);
}