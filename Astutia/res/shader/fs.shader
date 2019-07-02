#version 330 core

in vec2 texCoords;

out vec4 color;

uniform sampler2D diffuse_texture;

void main()
{
	color = texture(diffuse_texture, texCoords);
}
