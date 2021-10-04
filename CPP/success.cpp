#include "render/success.hpp"

Success::Success():  success(0){};

GLvoid Success::CheckShader(GLuint& shaderID, const GLenum type)
{
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if (!success)
    {
       GLchar infoLog[1024];
       glGetProgramInfoLog(shaderID, 1024, nullptr, infoLog);
       switch (type)
       {
       case 36313:
           std::cerr << "ERROR :: GeometryShader : Compile - time error : \n" << infoLog << std::endl;
           break;
       case 35632:
           std::cerr << "ERROR ::  FragmentShader : Compile - time error : \n" << infoLog << std::endl;
           break;
       case 35633:
           std::cerr << "ERROR ::  VertexShader : Compile - time error : \n" << infoLog << std::endl;
           break;
       }
    }
}

GLvoid Success::CheckProgram(GLuint& ProgramID)
{
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &success);
    if (!success)
    {
        GLchar infoLog[1024];
        glGetShaderInfoLog(ProgramID, 1024, nullptr, infoLog);
        std::cerr << "ERROR::SHADER: Link-time error:\n" << infoLog << std::endl;
    }
}

GLvoid Success::CheckOpen(std::ifstream& Shaderfile, const std::string & Shader, const GLenum type)
{
    Shaderfile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        Shaderfile.open(Shader);
    }
    catch (std::ifstream::failure& e)
    {
        switch (type)
        {
        case 36313:
            std::cerr << "I cant open GeometryShader file";
            break;
        case 35632:
            std::cerr << "I cant open FragmentShader file";
            break;
        case 35633:
            std::cerr << "I cant open VertexShader file";
            break;
        }
    }
}

GLvoid Success::CheckFBO()
{
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cerr << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
}
