#version 330 core
layout (location = 0) in vec3 inPos;
//layout (location = 1) in vec3 inColor;
layout (location = 1) in vec3 inTexDir; // vec3 because cubemap

out vec3 texDir;
//out vec3 color;
//uniform vec3 inColor;
//uniform mat4 transform;

uniform mat4 model;
uniform mat4 proj;
uniform mat4 view;

void main()
{
	gl_Position = proj * view * model * vec4(inPos, 1.0); // sums up all matrices
	//color = inColor;
	texDir = inTexDir;
}