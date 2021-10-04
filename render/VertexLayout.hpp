#ifndef _VERTEXLAYOUT_HPP_
#define _VERTEXLAYOUT_HPP_

#include<vector>
#include<glad/glad.h>
#include <cassert>
struct VertexBufferElement
{
	GLuint type;
	GLuint  count;
	GLboolean normalized;
	GLuint offset;
	GLuint Stride;
	static GLuint OffSize(GLuint type)
	{
		switch (type)
		{
		case GL_FLOAT: return 4;
		case GL_UNSIGNED_INT: return 4;
		case GL_UNSIGNED_BYTE: return 1;
		}
		assert(false);
		return 0;
	}
};

class VertexBufferLayout
{
public:

	friend class VertexArray;

	VertexBufferLayout():finishPoint(0){}
	template < typename T>
	GLvoid Push(GLuint count, GLuint Stride, GLuint offset)
	{
		static_assert(false);
	}
	template<>
	GLvoid Push< float >(GLuint  count, GLuint  Stride, GLuint  offset)
	{
		Elements.push_back({ GL_FLOAT, count, false, offset, Stride });
	}

	template <>
	GLvoid Push< GLuint >(GLuint  count, GLuint  Stride, GLuint  offset)
	{
		Elements.push_back({ GL_UNSIGNED_INT, count, false, Stride });
	}
	template <>
	GLvoid Push< GLboolean >(GLuint count, GLuint  Stride, GLuint  offset)
	{
		Elements.push_back({ GL_UNSIGNED_BYTE, count, true, Stride });
	}

	inline  const  std::vector <VertexBufferElement>  GetElements() const { return  Elements; }
	inline GLuint getFinishPoint() { return this->finishPoint; }

private:
	std::vector<VertexBufferElement> Elements;
	mutable  GLuint finishPoint;
};

#endif