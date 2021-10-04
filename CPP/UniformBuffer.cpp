#include "render/UniformBuffer.hpp"

template<typename T>
GLvoid UniformBuffer::BufferMemoryAllocate(GLuint offset, GLuint size, T& data)
{
	 glBufferSubData(GL_UNIFORM_BUFFER, offset, size, &data);
}

template<>
GLvoid UniformBuffer::BufferMemoryAllocate<glm::mat4>(GLuint offset, GLuint size, glm::mat4& data)
{
	glBufferSubData(GL_UNIFORM_BUFFER, offset, size, glm::value_ptr(data));
}

UniformBuffer::UniformBuffer(GLuint size): uniform_block_size(size)
{
	glGenBuffers(1, &this->ID);
	glBindBuffer(GL_UNIFORM_BUFFER, this->ID);
	glBufferData(GL_UNIFORM_BUFFER, this->uniform_block_size, nullptr, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}


UniformBuffer::~UniformBuffer()
{
	glDeleteBuffers(1, &this->ID);
}


GLvoid UniformBuffer::Bind(GLuint slot) const
{
	 glBindBuffer(GL_UNIFORM_BUFFER, this->ID);
}


GLvoid UniformBuffer::UnBind() const
{
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

GLuint UniformBuffer::GetID()
{
	return this->ID;
}

GLvoid UniformBuffer::SetBindRange(GLuint bind_index, GLuint offset, GLuint size)
{
	glBindBufferRange(GL_UNIFORM_BUFFER, bind_index, this->ID, offset, size);
}
