#ifndef _INDEXBUFFER_HPP_
#define _INDEXBUFFER_HPP_

#include "GLobject.hpp"

class IndexBuffer : public GLobject
{
private:
	GLint Count;
public:
    
	IndexBuffer();
	IndexBuffer(GLuint* data, GLuint count);
	IndexBuffer(const IndexBuffer&) = delete;
	IndexBuffer(IndexBuffer&& indexBuffer) noexcept;

	IndexBuffer& operator = (const IndexBuffer&) = delete;
	IndexBuffer& operator = (IndexBuffer&& indexBuffer) noexcept;

	~IndexBuffer() override;

	GLvoid Bind(GLuint slot = 0) const override;
	GLvoid UnBind() const override;
	GLuint GetID() override;
	void init(const void* data, GLuint count);
	inline GLuint GetCount() const { return this->Count; }

};

#endif