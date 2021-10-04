#ifndef _RENDER_HPP_
#define _RENDER_HPP_

#include "VertexArray.hpp"
#include "IndexBuffer.hpp"
#include "Camera.hpp"
#include<iostream>
#include<cstdarg>

enum GL_DRAW {
	GL_ARRAYS,
	GL_ELEMENTS,
	GL_INSTANCED_ARRAYS,
	GL_INSTANCED_ELEMENTS
};

class Render {
public:

	Render();

	Render(const Render&) = delete;
	Render(Render&&) noexcept = delete;
	Render& operator =(const Render&) = delete;
	Render& operator = (Render&&) noexcept = delete;

	GLvoid ProcessInput();
	GLvoid ResizeWindow(const GLuint height, const GLuint width);
	GLvoid disableCursor();


	GLvoid InitGLfW();
	GLvoid InitGLAD();

	GLvoid CreateWindow(GLuint width, GLuint height, const GLchar* name);

	GLFWwindow* GetWindow();

	GLvoid Clean();
	GLvoid Color(GLfloat f1, GLfloat f2, GLfloat f3, GLfloat f4);

	GLvoid Enable(GLuint count, ...);
	GLvoid Disable(GLuint count,...);

	template<GL_DRAW T>
		GLvoid draw(GLuint count, VertexArray& VAO, GLuint object_count = 1, GLenum primitiv = GL_TRIANGLES);
	template<>
	    GLvoid draw<GL_ARRAYS>(GLuint count, VertexArray& VAO, GLuint object_count, GLenum primitiv);
	template<>
	   GLvoid draw<GL_ELEMENTS>(GLuint count, VertexArray& VAO, GLuint object_count, GLenum primitiv);
	template<>
	   GLvoid draw < GL_INSTANCED_ARRAYS >(GLuint count, VertexArray& VAO, GLuint object_count, GLenum primitiv);
	template<>
	   GLvoid draw <GL_INSTANCED_ELEMENTS>(GLuint count, VertexArray& VAO, GLuint object_count, GLenum primitiv);
	  

	   bool blinn, blinnKeyPressed;
	   bool gammaEnabled, gammaKeyPressed;

private:
	   GLuint width, height;
	   GLFWwindow* window;
};


#endif
