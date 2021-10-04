#ifndef _FRAMEBUFFER_HPP_
#define _FRAMEBUFFER_HPP_

#include "GLobject.hpp"
#include "RenderBuffer.hpp"
#include "Texture2D.hpp"

enum GL_FRAME {
	GLTexture,
	GLRenderBuffer
};


template < GL_FRAME T>
class FrameBuffer : public GLobject {
public:
	FrameBuffer()
	{
		static_assert(false);
	}
};

template<>
class FrameBuffer <GLTexture> : public GLobject
{
public:
	FrameBuffer(GLuint width = 600, GLuint height = 400);
	FrameBuffer(const FrameBuffer&) = delete;
	FrameBuffer(FrameBuffer&&) noexcept = delete;

	FrameBuffer& operator = (const FrameBuffer&) = delete;
	FrameBuffer& operator = (FrameBuffer&&) noexcept = delete;

	~FrameBuffer() override;

	GLvoid Bind(const GLuint slot = 0) const override;
	GLvoid UnBind() const override;
	GLuint GetID() override;

	GLvoid AttachColor(const GLuint slot = 0);
	GLvoid AttachBuffer(const GLenum type, const GLuint slot = 0);

	Texture2D& GetTexture();


protected:
	GLuint texture;
    GLuint width;
	GLuint height;
	Texture2D tex;
};

template<>

class FrameBuffer <GLRenderBuffer> : public FrameBuffer<GLTexture>
{
public:
	FrameBuffer(GLuint width = 600, GLuint height = 400);

	GLvoid AttachBuffer(const GLenum type, RenderBuffer& rbo, GLuint slot = 0);
private:
};
#endif