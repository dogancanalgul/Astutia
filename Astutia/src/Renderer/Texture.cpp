#include "Texture.h"
#include "stb_image.h"

Texture::Texture(const std::string& filePath, const std::string type, int bindType, int coordType)
	: id(0), type(type), width(0), height(0), bpp(0)
{
	glGenTextures(1, &id);
	glBindTexture(bindType, id);

	//loadImage
	stbi_set_flip_vertically_on_load(true);

	unsigned char* image = stbi_load(filePath.c_str(), &width, &height, &bpp, 4);
	glTexParameteri(bindType, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(bindType, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(bindType, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(bindType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(coordType, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(bindType);

	stbi_image_free(image);
}
Texture::~Texture() {
	glDeleteTextures(1, &id);
}
void Texture::bind(unsigned int slot) {
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, id);
}
void Texture::unbind() const {
	glBindTexture(GL_TEXTURE_2D, 0);
}