#region Vertex
#version 440 core

layout(location = 0) in vec3 a_Pos;
layout(location = 1) in vec3 a_Norm;
layout(location = 2) in vec2 a_texCoord;
layout(location = 3) in vec3 a_tan;
layout(location = 4) in vec3 a_Bitan;

out vec3 fragmentPos;
out vec3 normal;
out vec2 texCoord;

uniform mat4 u_model;
uniform mat4 u_vp;


void main()
{
	fragmentPos = vec3(u_model * vec4(a_Pos, 1.0));
	normal = mat3(transpose(inverse(u_model))) * a_Norm;
	texCoord = vec2(a_texCoord.x, a_texCoord.y);
	gl_Position = u_vp * u_model * vec4(a_Pos, 1);
}

#region Fragment
#version 440 core

layout(location = 0)
out vec4 colour;

in vec3 normal;
in vec3 fragmentPos;
in vec2 texCoord;

uniform sampler2D u_texData;

void main()
{
	colour = texture(u_texData, texCoord);
}