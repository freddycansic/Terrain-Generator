#version 330 core
out vec4 FragColor;

//in vec3 color;
in vec3 texDir; // in out from vert

uniform samplerCube cubeMap;

void main()
{
   FragColor = texture(cubeMap, texDir);
}