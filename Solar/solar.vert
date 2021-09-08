//vertex shader
#version 330 core
layout(location = 0) in vec3 Pos;
layout(location = 1) in vec3 Color;
uniform mat4 Projection;
uniform mat4 View;
out vec3 vertexColor;
out vec3 vertexPos;

void main()
{
	gl_Position = Projection * View * vec4(Pos.x, Pos.y, Pos.z, 1.0);
	vertexColor = Color;
	vertexPos = Pos;
}