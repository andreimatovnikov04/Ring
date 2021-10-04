#include "render/Shader.hpp"
#pragma warning(disable : 4101)
GLvoid Shader::ReadingFromFiles(const GLchar* vx, const GLchar* fr, const GLchar* gm)
{
    std::string VertexShader = vx;
    std::string FragmentShader = fr;

    suc.CheckOpen(vShaderfile, VertexShader, GL_VERTEX_SHADER);
    suc.CheckOpen(frShaderfile, FragmentShader, GL_FRAGMENT_SHADER);

    vShaderStream << vShaderfile.rdbuf(); // сам процесс
    frShaderStream << frShaderfile.rdbuf();// сам процесс

    VertexCode = vShaderStream.str();
    FragmentCode = frShaderStream.str();

    if (gm != nullptr) {
        std::string GeometryShader = gm;
        suc.CheckOpen(gShaderfile, GeometryShader, GL_GEOMETRY_SHADER);

        gShaderStream << gShaderfile.rdbuf(); // сам процесс
        GeometryCode = gShaderStream.str();
        gShaderfile.close();
    }
    vShaderfile.close();
    frShaderfile.close();
}


GLuint Shader::createShader(const std::string& source, const GLenum shaderType, GLuint& shaderID)
{
    shaderID = glCreateShader(shaderType);
    const char* code = source.c_str();
    glShaderSource(shaderID, 1, &code, nullptr);
    glCompileShader(shaderID);
    suc.CheckShader(shaderID, shaderType);

    return shaderID;
}

GLvoid Shader::Program(GLuint vs, GLuint fr, GLuint gm)
{
    ID = glCreateProgram();
    glAttachShader(ID, vs);
    glAttachShader(ID, fr);
    if (gPath != nullptr) glAttachShader(ID, gm);
    glLinkProgram(ID);
    suc.CheckProgram(ID);
}


GLint Shader::GetUniformLocation(const std::string& name)
{
    if (UniformLocationCashe.find(name) != UniformLocationCashe.end()) return UniformLocationCashe[name];
    GLint location = glGetUniformLocation(ID, name.c_str());
    if (location == -1)
        std::cout << " Sorry I cant include " << name << " locaton!\n";
    UniformLocationCashe[name] = location;
    return location;
}


GLvoid Shader::Bind() const
{
    glUseProgram(ID);
}

GLvoid Shader::UnBind() const
{
    glUseProgram(0);
}


GLvoid Shader::SetUniform4f(const std::string& name, GLfloat f1, GLfloat f2, GLfloat f3, GLfloat f4)
{
    glUniform4f(GetUniformLocation(name), f1, f2, f3, f4);
}

GLvoid Shader::SetUniform1f(const std::string& name, GLfloat f1)
{
    glUniform1f(GetUniformLocation(name), f1);
}

GLvoid Shader::SetUniform1i(const std::string& name, GLint value)
{
    glUniform1i(GetUniformLocation(name), value);
}

GLvoid Shader::SetMatrixUniform4fv(const std::string& name, const glm::mat4 matrix)
{
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
}
GLvoid Shader::SetVec3Uniform3fv(const std::string& name, const glm::vec3& matrix)
{
    glUniform3fv(GetUniformLocation(name), 1, &matrix[0]);
}
GLvoid Shader::SetVec3Uniform3f(const std::string& name, GLfloat f1, GLfloat f2, GLfloat f3)
{
    glUniform3f(GetUniformLocation(name), f1, f2, f3);
}

GLvoid Shader::SetUniform2i(const std::string& name, GLint f1, GLint f2)
{
    glUniform2i(GetUniformLocation(name), f1, f2);
}

GLvoid Shader::SetUniform3i(const std::string& name, GLint f1, GLint f2, GLint f3)
{
    glUniform3i(GetUniformLocation(name), f1, f2, f3);
}

GLvoid Shader::SetVec3Uniform2f(const std::string& name, GLfloat f1, GLfloat f2)
{
    glUniform2f(GetUniformLocation(name), f1, f2);
}

GLvoid Shader::SetVec2Uniform2fv(const std::string& name, const glm::vec2& matrix)
{
    glUniform2fv(GetUniformLocation(name), 1, &matrix[0]);
}

GLvoid Shader::SetMatrixUniform2fv(const std::string& name, const glm::mat2& matrix)
{
    glUniform2fv(GetUniformLocation(name), 1, &matrix[0][0]);
}

GLvoid Shader::SetMatrixUniform3fv(const std::string& name, const glm::mat3& matrix)
{
    glUniform3fv(GetUniformLocation(name), 1, &matrix[0][0]);
}

GLvoid Shader::SetUniform1b(const std::string& name, bool f1)
{
    glUniform1i(GetUniformLocation(name), f1);
}

GLvoid Shader::SetVec3Uniform1f(const std::string& name, GLfloat f1)
{
    glUniform1f(GetUniformLocation(name), f1);
}


GLvoid Shader::scale(glm::mat4& model, glm::vec3 pos)
{
    model = glm::scale(model, pos);
}

void Shader::BindUnifromBufferPoint(const std::string& name, const GLuint bind_index)
{
    GLuint block_index =  glGetUniformBlockIndex(this->ID, name.c_str());
    glUniformBlockBinding(this->ID, block_index, bind_index);
}


GLvoid Shader::rotate(glm::mat4& model, GLfloat deg, glm::vec3 pos)
{
    model = glm::rotate(model, static_cast<float>(glm::radians(deg) * glfwGetTime()), pos);
}
GLvoid Shader::translate(glm::mat4& model, glm::vec3 pos)
{
    model = glm::translate(model, pos);
}


Shader::Shader(const GLchar* vertexShaderLink, const GLchar* fragmentShaderLink, const GLchar* geometryShaderLink):
    vPath(vertexShaderLink), frPath(fragmentShaderLink), gPath(geometryShaderLink)
{
    r.InitGLAD();
    GLuint fID, vID, gID;
    ReadingFromFiles(vertexShaderLink, fragmentShaderLink, geometryShaderLink);

    GLuint vertexShader = createShader(VertexCode, GL_VERTEX_SHADER, vID);
    GLuint fragmentShader = createShader(FragmentCode, GL_FRAGMENT_SHADER, fID);
    GLuint geometryShader = 0;
    if (gPath != nullptr) 
    {
        geometryShader = createShader(GeometryCode, GL_GEOMETRY_SHADER, gID);
    }

    Program(vertexShader, fragmentShader, geometryShader);
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    if(gPath != nullptr)  glDeleteShader(geometryShader);
}

Shader::~Shader()
{
    glDeleteProgram(this->ID);
}
