#version 330 core
layout (location = 0) in vec3 inPos;
//layout (location = 1) in vec3 inColor;
layout (location = 1) in vec2 inTexCoords;

out vec2 texCoords;
out vec3 color;
//uniform vec3 inColor;
//uniform mat4 transform;

uniform mat4 model;
uniform mat4 proj;
uniform mat4 view;

void main()
{
	gl_Position = vec4(inPos, 1.0) * model * proj * view; // sums up all matrices
	//color = inColor;
	texCoords = inTexCoords;
}