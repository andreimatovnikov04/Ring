#include "render/Render.hpp"

#include "render/Camera.hpp"

Render::Render() : window(nullptr), blinn(false), blinnKeyPressed(false), 
width(0), height(0), gammaEnabled(false), gammaKeyPressed(false) {}

GLvoid Render::ProcessInput()
{
	if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(this->window, GLFW_KEY_B) == GLFW_PRESS && !blinnKeyPressed)
    {
        blinn = !blinn;
        blinnKeyPressed = true;
    }
    if (glfwGetKey(this->window, GLFW_KEY_B) == GLFW_RELEASE)
    {
        blinnKeyPressed = false;
    }

    if (glfwGetKey(this->window, GLFW_KEY_SPACE) == GLFW_PRESS && !gammaKeyPressed)
    {
        gammaEnabled = !gammaEnabled;
        gammaKeyPressed = true;
    }
    if (glfwGetKey(this->window, GLFW_KEY_SPACE) == GLFW_RELEASE)
    {
        gammaKeyPressed = false;
    }
}

GLvoid Render::ResizeWindow(const GLuint height, const GLuint width)
{
    glfwSetFramebufferSizeCallback(this->window, [](GLFWwindow* window, GLint  height, GLint width) {
        glViewport(0, 0, height, width);
        });

    this->width = width;
    this->height = height;
}

GLvoid Render::disableCursor()
{
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

GLvoid Render::InitGLfW()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);
}

GLvoid Render::InitGLAD()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "I cant load glad";
        exit(1);
    }
}

GLvoid Render::CreateWindow(GLuint width, GLuint height, const GLchar* name)
{
    window = glfwCreateWindow(width, height, " Proffessional", NULL, NULL);
    if (!window) {
        std::cerr << "I cant create window";
        glfwTerminate();
    }
    this->width = width;
    this->height = height;

    glfwMakeContextCurrent(window);

}

GLFWwindow* Render::GetWindow()
{
    return this->window;
}


GLvoid Render::Clean()
{
    glfwPollEvents();
    glfwSwapBuffers(this->window);
}


GLvoid Render::Color(GLfloat f1, GLfloat f2, GLfloat f3, GLfloat f4)
{
    glClearColor(f1, f2, f3, f4);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

GLvoid Render::Enable(GLuint count, ...)
{
    va_list enable_list;
    va_start(enable_list, count);
    
    for (int i = 0; i < count; ++i)
        glEnable(va_arg(enable_list, GLenum));

    va_end(enable_list);
}

GLvoid Render::Disable(GLuint count, ...)
{
    va_list disable_list;
    va_start(disable_list, count);

    for (int i = 0; i < count; ++i)
        glDisable(va_arg(disable_list, GLenum));

    va_end(disable_list);
}

template<GL_DRAW T>
inline GLvoid Render::draw(GLuint count, VertexArray& VAO, GLuint object_count, GLenum primitiv)
{
    static_assert(false);
}

template<>
GLvoid Render::draw<GL_ARRAYS>(GLuint count, VertexArray& VAO, GLuint object_count, GLenum primitiv)
{
    VAO.Bind();
    glDrawArrays(primitiv, 0, count);
    VAO.UnBind();
}
template<>
GLvoid Render::draw<GL_ELEMENTS>(GLuint count, VertexArray& VAO,GLuint object_count, GLenum primitiv)
{
    VAO.Bind();
    glDrawElements(primitiv, count, GL_UNSIGNED_INT, 0);
    VAO.UnBind();
}

template<>
GLvoid Render::draw<GL_INSTANCED_ARRAYS>(GLuint count, VertexArray& VAO, GLuint object_count, GLenum primitiv)
{
    VAO.Bind();
    glDrawArraysInstanced(primitiv, 0, count, object_count);
    VAO.UnBind();
}

template<>
inline GLvoid Render::draw<GL_INSTANCED_ELEMENTS>(GLuint count, VertexArray& VAO, GLuint object_count, GLenum primitiv)
{
    VAO.Bind();
    glDrawElementsInstanced(primitiv, count, GL_UNSIGNED_INT, 0, object_count);
    VAO.UnBind();
}
