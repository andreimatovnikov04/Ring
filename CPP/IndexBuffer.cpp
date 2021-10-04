#include "render/IndexBuffer.hpp"

IndexBuffer::IndexBuffer():Count(0){}
IndexBuffer::IndexBuffer(GLuint* data, GLuint count) : Count(0)
{
	init(data, count);
}

IndexBuffer::IndexBuffer(IndexBuffer&& indexBuffer) noexcept
{
	this->ID = indexBuffer.ID;
	this->Count = indexBuffer.Count;
	indexBuffer.Count = 0;
	indexBuffer.ID = 0;
}
IndexBuffer& IndexBuffer::operator=(IndexBuffer&& indexBuffer) noexcept
{
	this->ID = indexBuffer.ID;
	this->Count = indexBuffer.Count;
	indexBuffer.Count = 0;
	indexBuffer.ID = 0;
	return *this;
}
IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &ID);
}

GLvoid IndexBuffer::Bind(GLuint slot) const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

GLvoid IndexBuffer::UnBind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

GLuint IndexBuffer::GetID()
{
	return this->ID;
}

void IndexBuffer::init(const void* data, GLuint count)
{
	gladLoadGLLoader(GLADloadproc(glfwGetProcAddress));
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW);
}
