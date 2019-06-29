#pragma once
#include "Buffers.h"
#include <memory>

class VertexArray{
public:
	VertexArray();
	VertexArray(const std::shared_ptr<VertexBuffer>& vb);
	VertexArray(const std::shared_ptr<VertexBuffer>& vb, const std::shared_ptr<IndexBuffer>& ib);
	~VertexArray();

	void addBuffer(const std::shared_ptr<VertexBuffer>& vb);
	void setIndexBuffer(const std::shared_ptr<IndexBuffer>& vb);

	inline const std::shared_ptr<IndexBuffer>& getIndexBuffer() { return indexBuffer;  }
	void bind() const;
	void unbind() const;
private:
	unsigned int id;
	std::vector<std::shared_ptr<VertexBuffer>> vertexBuffers;
	std::shared_ptr<IndexBuffer> indexBuffer;
};

