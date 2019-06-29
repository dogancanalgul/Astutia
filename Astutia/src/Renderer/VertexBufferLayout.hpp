#pragma once
#include <vector>
#include <glad/glad.h>
struct VertexBufferElement
{
	unsigned int size;
	unsigned int type;

	static unsigned int sizeofType(unsigned int type) {
		switch (type) {
		case GL_FLOAT:
			return sizeof(float);
		case GL_UNSIGNED_INT:
			return sizeof(unsigned int);
		}
		return -1;
	}
};

class VertexBufferLayout {
public:

	template<typename T>
	void push(unsigned int count) {
		return;
	}
	template<>
	void push<float>(unsigned int count) {
		elements.push_back({ count, GL_FLOAT });
		stride += count * sizeof(GL_FLOAT);
	}

	inline const std::vector<VertexBufferElement>& getElements() const{ return elements; }
	inline unsigned int getStride() const{ return stride; }
private:
	std::vector<VertexBufferElement> elements;
	unsigned int stride = 0;

};