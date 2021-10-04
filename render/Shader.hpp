#ifndef SHADER_HPP
#define SHADER_HPP

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include <cassert>
#include<unordered_map>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Render.hpp"
#include "Success.hpp"
class Shader
{
private:

    std::string VertexCode;
    std::string FragmentCode;
    std::string GeometryCode;

    std::ifstream vShaderfile;
    std::ifstream frShaderfile;
    std::ifstream gShaderfile;

    std::stringstream  vShaderStream, frShaderStream, gShaderStream;

    const GLchar* vPath;
    const GLchar* frPath;
    const GLchar* gPath;

    Success suc;
    Render r;

    std::unordered_map < std::string, GLint > UniformLocationCashe;
    GLvoid ReadingFromFiles(const GLchar* vx, const GLchar* fr, const GLchar* gm);
    GLuint createShader(const std::string& source, const GLenum shaderType, GLuint& shaderID);
    GLvoid Program(GLuint vs, GLuint fr, GLuint gm);
    GLint GetUniformLocation(const std::string& name);

public:
    GLuint ID;
    GLvoid Bind() const;
    GLvoid UnBind() const;

    GLvoid SetUniform4f(const std::string& name, GLfloat f1, GLfloat f2, GLfloat f3, GLfloat f4);
    GLvoid SetUniform1f(const std::string& name, GLfloat f1);
    GLvoid SetUniform1i(const std::string& name, GLint value);
    GLvoid SetMatrixUniform4fv(const std::string& name, const glm::mat4 matrix);
    GLvoid SetVec3Uniform3fv(const std::string& name, const glm::vec3& matrix);
    GLvoid SetVec3Uniform1f(const std::string& name, GLfloat f1);
    GLvoid SetVec3Uniform3f(const std::string& name, GLfloat f1, GLfloat f2, GLfloat  f3);
    GLvoid SetUniform2i(const std::string& name, GLint f1, GLint f2);
    GLvoid SetUniform3i(const std::string& name, GLint f1, GLint f2, GLint f3);
    GLvoid SetVec3Uniform2f(const std::string& name, GLfloat f1, GLfloat f2);
    GLvoid SetVec2Uniform2fv(const std::string& name, const glm::vec2& matrix);
    GLvoid SetMatrixUniform2fv(const std::string& name, const glm::mat2& matrix);
    GLvoid SetMatrixUniform3fv(const std::string& name, const glm::mat3& matrix);
    GLvoid SetUniform1b(const std::string& name, bool f1);

    GLvoid rotate(glm::mat4&, GLfloat deg, glm::vec3);
    GLvoid translate(glm::mat4&, glm::vec3);
    GLvoid scale(glm::mat4&, glm::vec3);

    void  BindUnifromBufferPoint(const std::string& name, GLuint index);

    Shader(const GLchar* vertexShaderLink, const GLchar* fragmentShaderLink, const GLchar* geometryShaderLink = nullptr);
    ~Shader();
};

#endif
