#include "render/VertexBuffer.hpp"

VertexBuffer::VertexBuffer() {}
VertexBuffer::VertexBuffer(const void* data, GLuint size)
{
	init(data, size);
}

VertexBuffer::VertexBuffer(VertexBuffer&& vertexBuffer) noexcept
{
	this->ID = vertexBuffer.ID;
	vertexBuffer.ID = 0;

}

VertexBuffer& VertexBuffer::operator=(VertexBuffer&& vertexBuffer) noexcept
{
	this->ID = vertexBuffer.ID;
	vertexBuffer.ID = 0;
	return *this;
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &ID);
}

GLvoid VertexBuffer::Bind(GLuint slot) const
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

GLvoid VertexBuffer::UnBind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

GLuint VertexBuffer::GetID()
{
	return this->ID;
}

void VertexBuffer::init(const void* data, GLuint size)
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "I cant load glad";
		exit(1);
	}
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

GLvoid VertexBuffer::update(const void* data, GLuint size)
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}


