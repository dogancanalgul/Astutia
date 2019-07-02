#pragma once
#include <string>
#include <glad/glad.h>
class Texture {
public:
	Texture(const std::string& filePath, const std::string type = "diffuse_texture", int bindType = GL_TEXTURE_2D, int coordType = GL_TEXTURE_2D);
	~Texture();

	void bind(unsigned int slot = 0);
	void unbind() const;

	inline unsigned int getId() const { return this->id; };
	inline const char* getType() const { return this->type.c_str(); };
private:
	unsigned int id;
	std::string type;
	int width, height, bpp;
};