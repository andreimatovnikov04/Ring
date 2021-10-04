#ifndef _RENDERBUFFER_HPP_
#define _RENDERBUFFER_HPP_

#include "GLobject.hpp"

class RenderBuffer : public GLobject 
{
public:
	RenderBuffer(GLuint width = 600, GLuint height = 400);
	RenderBuffer(const RenderBuffer&) = delete;
	RenderBuffer(RenderBuffer&&) noexcept;

	RenderBuffer& operator = (const RenderBuffer&) = delete;
	RenderBuffer& operator = (RenderBuffer&&) noexcept;

	~RenderBuffer() override;

	GLvoid Bind(const GLuint slot = 0) const override;
	GLvoid UnBind() const override;
	GLuint GetID() override;
	GLvoid RenderAttach(const GLenum type);
	GLuint& GetRenderBuffer();

private:
	 GLuint width;
	 GLuint height;
};

#endif