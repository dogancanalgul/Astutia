#include "VertexArray.h"

VertexArray::VertexArray() {
	glGenVertexArrays(1, &id);
}

VertexArray::VertexArray(const std::shared_ptr<VertexBuffer>& vb) :VertexArray(){
	addBuffer(vb);
}
VertexArray::VertexArray(const std::shared_ptr<VertexBuffer>& vb, const std::shared_ptr<IndexBuffer>& ib) : VertexArray(vb) {
	setIndexBuffer(ib);
}

VertexArray::~VertexArray(){
	glDeleteVertexArrays(1, &id);
}

void VertexArray::addBuffer(const std::shared_ptr<VertexBuffer>& vb) {
	glBindVertexArray(id);
	vb->bind();

	const auto& elements = vb->layout.getElements();
	unsigned int offset = 0;

	for (unsigned int i = 0; i < elements.size(); ++i) {
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, elements[i].size, elements[i].type, GL_FALSE, vb->layout.getStride(), (const void *)offset);
		offset += elements[i].size * VertexBufferElement::sizeofType(elements[i].type);
	}

	vertexBuffers.push_back(vb);
}
void VertexArray::setIndexBuffer(const std::shared_ptr<IndexBuffer>& ib) {
	glBindVertexArray(id);
	ib->bind();
	indexBuffer = ib;
}
void VertexArray::bind() const {
	glBindVertexArray(id);
}
void VertexArray::unbind() const {
	glBindVertexArray(0);
}