#region Vertex
#version 440 core

layout(location = 0) in vec3 a_particlePosition;

uniform mat4 u_model;

void main()
{
	gl_Position = u_model * vec4(a_particlePosition,1.0f);
}

#region Geomatry
#version 440 core
layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

layout (std140) uniform VP
{
	mat4 u_projection;
	mat4 u_view;
};

uniform mat4 u_model;

void main() 
{    
	vec3 position = gl_in[0].gl_Position.xyz;
	
	gl_Position = u_projection * u_view * vec4(position + vec3(-1.0f,-1.0f,0.0f),1.0f);
	EmitVertex();
	gl_Position = u_projection * u_view * vec4(position + vec3(-1.0f,1.0f,0.0f),1.0f);
	EmitVertex();
	gl_Position = u_projection * u_view * vec4(position + vec3(1.0f,-1.0f,0.0f),1.0f);
	EmitVertex();
	gl_Position = u_projection * u_view * vec4(position + vec3(1.0f,1.0f,0.0f),1.0f);
	EmitVertex();
	EndPrimitive(); 
}

#region Fragment
#version 440 core

layout(location = 0) out vec4 colour;

void main()
{
	colour = vec4(0.5f,0.5f,0.5f,1.0f);
}