#include "render/VertexArray.hpp"
#pragma warning(disable: 4312)

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &ID);
}

VertexArray::VertexArray(VertexArray&& vertexArray) noexcept
{
	this->ID = vertexArray.ID;
	vertexArray.ID = 0;
}

VertexArray::VertexArray() {
	glGenVertexArrays(1, &ID);
	glBindVertexArray(ID);
};

VertexArray& VertexArray::operator=(VertexArray&& vertexArray) noexcept
{

	this->ID = vertexArray.ID;
	vertexArray.ID = 0;
	return *this;
}

GLvoid VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout, GLuint start_point)
{
	vb.Bind();  GLuint i = 0;
	const  auto& elements = layout.GetElements();
	for (i; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		GLuint  offset = element.offset * VertexBufferElement::OffSize(element.type);
		GLuint Stride = element.Stride * VertexBufferElement::OffSize(element.type);
		glEnableVertexAttribArray(i + start_point);
		glVertexAttribPointer(i + start_point, element.count, element.type,
			element.normalized ? GL_TRUE : GL_FALSE, Stride, (void*)offset); // инициализируем атрибуты вершин
	}
	layout.finishPoint = i;
}

GLvoid VertexArray::Bind(GLuint slot) const
{
	glBindVertexArray(ID);
}

GLvoid VertexArray::UnBind() const
{
	glBindVertexArray(0);
}

GLuint VertexArray::GetID()
{
	return this->ID;
}

GLvoid VertexArray::SetDevisor(GLuint attribut, GLuint divisor)
{
	glVertexAttribDivisor(attribut, divisor);
}



