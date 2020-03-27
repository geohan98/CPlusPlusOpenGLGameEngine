#region Vertex
#version 440 core

layout(location = 0) in vec3 a_Pos;

uniform mat4 u_model;
uniform mat4 u_vp;

void main()
{
	gl_Position = u_vp * u_model * vec4(a_Pos, 1);
}

#region Fragment
#version 440 core
layout(location = 0) out vec4 colour;

void main()
{
	colour = vec4(1.0,0.0,1.0,1.0);
}