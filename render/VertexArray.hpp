#ifndef _VERTEXARRAY_HPP_
#define _VERTEXARRAY_HPP_

#include "VertexLayout.hpp"
#include "VertexBuffer.hpp"
#include "GLobject.hpp"

class VertexArray : public GLobject
{
public:

	~VertexArray() override;

	VertexArray(const VertexArray&) = delete;
	VertexArray(VertexArray&& vertexArray) noexcept;
	VertexArray();

	VertexArray& operator = (const VertexArray&) = delete;
	VertexArray& operator = (VertexArray&& vertexArray) noexcept;

	GLvoid AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout, GLuint start_point = 0);

	GLvoid Bind(GLuint slot = 0) const override;
	GLvoid UnBind() const override;
	GLuint GetID() override;

	GLvoid SetDevisor(GLuint attribut, GLuint divisor);
};
#endif



