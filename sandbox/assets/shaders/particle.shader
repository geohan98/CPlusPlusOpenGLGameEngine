#region Vertex
#version 440 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in float a_rotation;
layout(location = 2) in vec2 a_scale;
layout(location = 3) in vec4 a_colour;

out float v_rotation;
out vec2 v_scale;
out vec4 v_colour;

uniform mat4 u_model;

void main()
{
	v_rotation = radians(a_rotation);
	v_scale = a_scale;
	v_colour = a_colour;
	gl_Position = u_model * vec4(a_position,1.0f);
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

in float v_rotation[];
in vec2 v_scale[];
in vec4 v_colour[];

out vec4 g_colour;

vec2 rotatePoint(float x, float y, float rotation)
{
	return vec2(x * cos(rotation) - y * sin(rotation),y * cos(rotation) + x * sin(rotation));
}

void main() 
{    
	mat4 vp = u_projection * u_view;
	vec3 cameraRight = vec3(u_view[0][0],u_view[1][0],u_view[2][0]);
	vec3 cameraUp = vec3(u_view[0][1],u_view[1][1],u_view[2][1]);
	vec3 position = gl_in[0].gl_Position.xyz;
	
	g_colour = v_colour[0];
	gl_Position = vp * vec4(position + cameraRight * rotatePoint(-0.5f,0.5f, v_rotation[0]).x + cameraUp * rotatePoint(-0.5f,0.5f, v_rotation[0]).y, 1.0f);
	EmitVertex();
	g_colour = v_colour[0];
	gl_Position = vp * vec4(position + cameraRight * rotatePoint(-0.5f,-0.5f,v_rotation[0]).x + cameraUp * rotatePoint(-0.5f,-0.5f,v_rotation[0]).y, 1.0f);
	EmitVertex();
	g_colour = v_colour[0];
	gl_Position = vp * vec4(position + cameraRight * rotatePoint(0.5f,0.5f,  v_rotation[0]).x + cameraUp * rotatePoint(0.5f,0.5f,  v_rotation[0]).y, 1.0f);
	EmitVertex();
	g_colour = v_colour[0];
	gl_Position = vp * vec4(position + cameraRight * rotatePoint(0.5f,-0.5f, v_rotation[0]).x + cameraUp * rotatePoint(0.5f,-0.5f, v_rotation[0]).y, 1.0f);
	EmitVertex();
	EndPrimitive(); 
}

#region Fragment
#version 440 core

layout(location = 0) out vec4 colour;

in vec4 g_colour;

void main()
{
	colour = g_colour;
}