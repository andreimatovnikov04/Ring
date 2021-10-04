#include "render/CubeMap.hpp"

CubeMap::CubeMap(std::array< const std::string, 6> faces)
{
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, ID);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    for (GLuint i = 0; i < faces.size(); i++)
    {
        stbi_set_flip_vertically_on_load(true);
        data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);

        if (data)
           glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA8, width, height, 0, 
               nrChannels == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
        else std::cerr << "Cubemap texture failed to load at path: " << faces[i] << std::endl;

        stbi_image_free(data);
    }

}

GLvoid CubeMap::Bind(GLuint slot) const
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_CUBE_MAP, ID);
}

GLvoid CubeMap::UnBind() const
{
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

CubeMap::~CubeMap()
{
    glDeleteTextures(GL_TEXTURE_CUBE_MAP, &ID);
}
