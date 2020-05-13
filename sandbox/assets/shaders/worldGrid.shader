#region Vertex
#version 440 core

layout(location = 0) in vec3 a_Pos;
layout(location = 1) in vec4 a_Colour;

out vec4 Colour;

uniform mat4 u_model;
uniform mat4 u_vp;


void main()
{
	Colour = a_Colour;
	gl_Position = u_vp * u_model * vec4(a_Pos, 1);
}

#region Fragment
#version 440 core

layout(location = 0) 
in vec4 Colour;
out vec4 colour;

void main()
{
	colour = vec4(Colour);
}