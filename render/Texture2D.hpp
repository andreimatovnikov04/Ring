#ifndef _TEXTURE_HPP_
#define _TEXTURE_HPP_

#include "GLobject.hpp"
#include<string>
#include<cassert>


#include <stb_image.h>

class Texture2D : GLobject
{
protected:
	const GLchar* file_path;
    GLboolean* data;
	GLint width, height, nrChannels;
	bool gamma;
public:
	std::string type;

	Texture2D(const GLchar* file_path, bool gamma_correction = false);
	Texture2D(const Texture2D&) = delete;
	Texture2D(Texture2D&& texture) noexcept;
	Texture2D();
	Texture2D(GLuint& ID);

	Texture2D & operator = (const Texture2D&) = delete;
	Texture2D& operator = (Texture2D&& texture) noexcept;
	Texture2D& operator = (GLuint& ID) noexcept;

    virtual ~Texture2D() override;

	virtual GLvoid Bind(GLuint slot = 0)  const override;
	virtual GLvoid UnBind() const override;
	virtual  GLuint GetID() override;
	GLvoid SetID(GLuint ID);

	const GLchar* GetPath();
	GLvoid SetPath(const GLchar* path);

	inline int GetWidth()const { return width; }
	inline int GetHeight() const { return height; }
};

#endif