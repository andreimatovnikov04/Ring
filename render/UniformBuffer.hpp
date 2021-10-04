#ifndef _UNIFORMBUFFER_HPP_
#define _UNIFORMBUFFER_HPP_

#include "GLobject.hpp"
class UniformBuffer : public GLobject
{
 public:
	 UniformBuffer(GLuint size);
	 UniformBuffer(const UniformBuffer&) = delete;
	 UniformBuffer(UniformBuffer&& ) = delete;

	 UniformBuffer& operator = (const UniformBuffer&) = delete;
	 UniformBuffer& operator = (UniformBuffer&&) = delete;

	 ~UniformBuffer() override;

	 GLvoid Bind(GLuint slot = 0) const override;
	 GLvoid UnBind() const override;
	 GLuint GetID() override;

	 template <typename T>
	 GLvoid BufferMemoryAllocate(GLuint offset, GLuint size, T& data);
	 template<>
	 GLvoid BufferMemoryAllocate<glm::mat4>(GLuint offset, GLuint size, glm::mat4& data);

	 GLvoid SetBindRange(GLuint bind_index, GLuint offset, GLuint size);
 private:
	 GLuint uniform_block_size;
};

#endif
