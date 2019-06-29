#pragma once
#include "VertexBufferLayout.hpp"

class VertexBuffer
{
public:
	VertexBufferLayout layout;
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void bind() const;
	void unbind() const;
private:
	unsigned int id;
};

class IndexBuffer
{
public:
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	void bind() const;
	void unbind() const;
	unsigned int getCount() const { return count; }
private:
	unsigned int id, count;

};