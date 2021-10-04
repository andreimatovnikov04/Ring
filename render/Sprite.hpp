#ifndef _SPRITE_HPP_
#define _SPRITE_HPP_


#include <memory>
#include "Shader.hpp"
#include "indexBuffer.hpp"
#include "Texture2D.hpp"

class Sprite : public Texture2D
{
public:
	struct FramesDescriptions
	{
		FramesDescriptions(glm::vec2 leftBottom, glm::vec2 topRight, const GLdouble duration) 
			:m_leftBottom(leftBottom), m_topRight(m_topRight), duration(duration) {}

		glm::vec2 m_leftBottom;
		glm::vec2 m_topRight;
		GLdouble duration;
	};

	Sprite(std::shared_ptr<Texture2D> texture_ptr,
		std::shared_ptr<Shader> shader_ptr);
	Sprite(const Sprite&) = delete;

	Sprite& operator = (const Sprite&) = delete;

	GLvoid draw(glm::vec3 position , glm::vec3 size, const GLuint frame_id, 
		const GLfloat rotation = 0.0f, const GLint layer = 0);

	GLvoid InsertFrames(std::vector <FramesDescriptions> framesDescriptions);
	GLdouble getFrameDuration(const GLuint frame_id) const;
	GLuint getFramesCount() const;


private:
	std::shared_ptr<Texture2D> m_texture_ptr;
	std::shared_ptr <Shader> m_shader_ptr;


	VertexBuffer m_VertexBuffer, m_textureBuffer;
	VertexArray m_VertexArray;
	IndexBuffer m_IndexBuffer;

	std::vector <FramesDescriptions> m_frames_descriptions;
	GLuint m_last_frame_id;

	Render m_render;
};

#endif