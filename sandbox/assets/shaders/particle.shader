#region Vertex
#version 440 core

layout(location = 0) in vec3 a_vertexPosition;
layout(location = 1) in vec3 a_vertexColour;

out vec3 v_FragColour;

layout (std140) uniform Matrices
{
	mat4 u_projection;
	mat4 u_view;
};

uniform mat4 u_model;


void main()
{
	v_FragColour = a_vertexColour;
	gl_Position = u_projection * u_view * u_model * vec4(a_vertexPosition, 1);
}

#region Geomatry
#version 440 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in vec3 v_FragColour[];

out vec3 g_FragColour;

void main() {    

  // loop through each vertex (3 because we're reading a triangle)
  for(int i = 0 ; i < 3; i++){
    gl_Position = gl_in[i].gl_Position ;
    g_FragColour = v_FragColour[i]; 
    EmitVertex() ;
  }
    EndPrimitive();
}

#region Fragment
#version 440 core

layout(location = 0) out vec4 colour;
in vec3 g_FragColour;
void main()
{
	colour = vec4(g_FragColour, 1.0);
}