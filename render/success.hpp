#ifndef _SUCCESS_HPP_
#define _SUCCESS_HPP_

#include <GLAD/glad.h>
#include<GLFW/glfw3.h>

#include<fstream>
#include<iostream>


class Success
{
public:
	Success(const Success&) = delete;
	Success(Success&&) noexcept = delete;
	Success();

	Success& operator = (const Success&) = delete;
	Success&& operator = (Success&&) noexcept = delete;

	GLvoid CheckShader(GLuint &ShaderID, const GLenum);
	GLvoid CheckProgram(GLuint &ProgramID);
	GLvoid CheckOpen(std::ifstream &, const std::string &, const GLenum);
	GLvoid CheckFBO();

private:
	GLint success;
};
#endif