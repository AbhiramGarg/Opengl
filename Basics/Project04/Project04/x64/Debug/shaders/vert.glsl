#version 460 core

layout(location=0) in vec3 Position;
layout(location=1) in vec3 VertexColor;

out vec3 v_vertexColors;

void main()
{
	v_vertexColors = VertexColor;
	gl_Position = vec4(Position.x,Position.y,Position.z,1.0f);
};