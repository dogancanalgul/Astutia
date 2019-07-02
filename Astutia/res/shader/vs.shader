#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_normal;
layout(location = 2) in vec2 a_texCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 texCoords;

void main()
{
	texCoords = a_texCoords;

	gl_Position = projection * view * model * vec4(a_Position, 1.0);

}
