#ifndef VERTEXBUFFER_HPP
#define VERTEXBUFFER_HPP

#include "GLobject.hpp"


class VertexBuffer: public GLobject
{
public:

	VertexBuffer();
	VertexBuffer(const void* data, GLuint size);
	VertexBuffer(const VertexBuffer&) = delete;
	VertexBuffer(VertexBuffer&& vertexBuffer) noexcept;

	VertexBuffer& operator =(VertexBuffer&& vertexBuffer) noexcept;
	VertexBuffer& operator = (const VertexBuffer&) = delete;

	~VertexBuffer() override;

	GLvoid Bind(GLuint slot = 0) const override;
	GLvoid UnBind() const override;
	GLuint GetID() override;
	GLvoid init(const void* data, GLuint size);
	GLvoid update(const void* data, GLuint size);


};
#endif