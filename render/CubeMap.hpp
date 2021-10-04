#ifndef _CUBEMAP_HPP_
#define _CUBEMAP_HPP_

#include "Texture2D.hpp"
#include<array>

class CubeMap : public Texture2D
{
public:
	CubeMap(std::array< const std:: string ,6> faces);
	CubeMap(const CubeMap&) = delete;
	CubeMap(CubeMap&&) noexcept = delete;

	CubeMap& operator = (const CubeMap&) = delete;
	CubeMap& operator = (CubeMap&&) noexcept = delete;
	
	GLvoid Bind( GLuint slot = 0) const override;
	GLvoid UnBind() const override;

	~CubeMap() override;
private:
	GLuint ID;
};
#endif
