#ifndef _GLOBJECT_H_
#define _GLOBJECT_H_

#pragma warning(disable: 26495)

#include <GLAD/glad.h>
#include<GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include<cassert>
#include <iostream>

class GLobject {
public:

	virtual ~GLobject() = 0;
protected:
	mutable GLuint ID;
	virtual GLvoid Bind( GLuint slot = 0)const = 0; 
	virtual GLvoid UnBind()const  = 0; 
	virtual GLuint GetID() = 0;
};

#endif
