#include "render/FrameBuffer.hpp"


FrameBuffer<GLTexture>::FrameBuffer(GLuint _width, GLuint _height) : width(_width), height(_height)
{
	glGenFramebuffers(1, &ID);
	glBindFramebuffer(GL_FRAMEBUFFER, ID);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


}

FrameBuffer<GLRenderBuffer>::FrameBuffer(GLuint width, GLuint height) : FrameBuffer<GLTexture>::FrameBuffer() {}

FrameBuffer<GLTexture>::~FrameBuffer()
{
	glDeleteBuffers(1, &ID);
}

GLvoid FrameBuffer<GLTexture>::Bind(const GLuint slot) const
{
	glBindFramebuffer(GL_FRAMEBUFFER, ID);
}

GLvoid FrameBuffer<GLTexture>::UnBind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

GLuint FrameBuffer<GLTexture>::GetID()
{
	return this->ID;
}


GLvoid FrameBuffer <GLTexture>::AttachBuffer(const GLenum type, const GLuint slot)
{
	glFramebufferTexture2D(GL_FRAMEBUFFER, type + slot, GL_TEXTURE_2D, texture, 0);
}


GLvoid FrameBuffer<GLTexture>::AttachColor(const GLuint slot)
{
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + slot, GL_TEXTURE_2D, texture, 0);
}

Texture2D& FrameBuffer <GLTexture>::GetTexture()
{
	this->tex = this->texture;
	return tex;
}


GLvoid FrameBuffer <GLRenderBuffer>::AttachBuffer(const GLenum type, RenderBuffer& rbo, const GLuint slot)
{
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, type + slot, GL_RENDERBUFFER, rbo.GetRenderBuffer());
}
