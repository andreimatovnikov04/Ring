#include "render/Texture2D.hpp"

Texture2D::Texture2D(const GLchar* path, bool gamma_correction) :  file_path(path), data(nullptr),
 width(0), height(0), nrChannels(0), gamma(gamma_correction)
{
	
	data = stbi_load(file_path, &width, &height, &nrChannels, 0);

	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	stbi_set_flip_vertically_on_load(1);

	if (data == nullptr) assert(false);
	else
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, 
			nrChannels == 4 ? (gamma ? GL_SRGB_ALPHA : GL_RGBA) : (gamma ? GL_SRGB : GL_RGB),	GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	stbi_image_free(data);
}

Texture2D::Texture2D(Texture2D&& texture) noexcept :
	file_path(texture.file_path),data(texture.data)
{
	this->ID = texture.ID;
	this->width = texture.width;
	this->height = texture.height;
	this->nrChannels = texture.nrChannels;
	texture.ID = 0;
}

Texture2D::Texture2D() : data(nullptr), width(0), height(0),
  nrChannels(0), file_path(nullptr)
{

}

Texture2D::Texture2D(GLuint& ID)
{
	this->ID = ID;
}

Texture2D& Texture2D::operator=(Texture2D&& texture) noexcept
{
	glDeleteTextures(1, &this->ID);
	this->ID = texture.ID;
	this->width = texture.width;
	this->height = texture.height;
	this->nrChannels = texture.nrChannels;
	texture.ID = 0;
	return *this;
}

Texture2D& Texture2D::operator=(GLuint& ID) noexcept
{
	this->ID = ID;
	return *this;
}

Texture2D::~Texture2D()
{
	glDeleteTextures(1, &ID);
}

GLvoid Texture2D::Bind(GLuint slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, ID);

}

GLvoid Texture2D::UnBind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint Texture2D::GetID()
{
	return this->ID;
}

GLvoid Texture2D::SetID(GLuint ID)
{
	this->ID = ID;
}

const GLchar* Texture2D::GetPath()
{
	return this->file_path;
}

GLvoid Texture2D::SetPath(const GLchar* path)
{
	this->file_path = path;
}
