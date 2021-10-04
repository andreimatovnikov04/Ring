#include "render/RenderBuffer.hpp"

RenderBuffer::RenderBuffer(GLuint _width, GLuint _height): width(_width), height(_height)
{
	glGenRenderbuffers(1, &ID);
	glBindRenderbuffer(GL_RENDERBUFFER, ID);
}

RenderBuffer::RenderBuffer(RenderBuffer&& renderBuffer) noexcept
	: width(renderBuffer.width), height(renderBuffer.height)
{
	this->ID = renderBuffer.ID;

	renderBuffer.ID = 0;
	renderBuffer.height = 0;
	renderBuffer.width = 0;

}

RenderBuffer& RenderBuffer::operator=(RenderBuffer&& renderBuffer) noexcept
{
	this->width = renderBuffer.width;
	this->height = renderBuffer.height;
	this->ID = renderBuffer.ID;

	renderBuffer.ID = 0;
	renderBuffer.height = 0;
	renderBuffer.width = 0;

	return *this;
}

RenderBuffer::~RenderBuffer()
{
	glDeleteBuffers(1, &ID);
}

GLvoid RenderBuffer::Bind(const GLuint slot) const
{
	glBindRenderbuffer(GL_RENDERBUFFER, ID);
}

GLvoid RenderBuffer::UnBind() const
{
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

GLuint RenderBuffer::GetID()
{
	return this->ID;
}

GLvoid RenderBuffer::RenderAttach(const GLenum type)
{
	glRenderbufferStorage(GL_RENDERBUFFER, type, width, height);
}

GLuint& RenderBuffer::GetRenderBuffer()
{
	return this->ID;
}

