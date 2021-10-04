#include "render/Sprite.hpp"

Sprite::Sprite(std::shared_ptr<Texture2D> texture_ptr, std::shared_ptr<Shader> shader_ptr)
	:m_shader_ptr(shader_ptr), m_texture_ptr(texture_ptr), m_last_frame_id(0)
{
	const GLfloat VertexCoords[] = {
       0.0f, 0.0f,
	   0.0f, 1.0f,
	   1.0f, 1.0f,
	   1.0f, 0.0f
	};

	const GLuint indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	m_VertexArray.Bind();
	m_VertexBuffer.init(VertexCoords, 2 * 4 * sizeof(GLfloat));
	m_textureBuffer.init(VertexCoords, 2 * 4 * sizeof(GLfloat));

	VertexBufferLayout vertexCoordslayout;
	vertexCoordslayout.Push<GLfloat>(2, 2, 0);
	m_VertexArray.AddBuffer(m_VertexBuffer, vertexCoordslayout);

	VertexBufferLayout textureCoordslayout;
	textureCoordslayout.Push<GLfloat>(2, 2, 0);
	m_VertexArray.AddBuffer(m_textureBuffer, textureCoordslayout);
	
	m_IndexBuffer.init(indices, 2 * 4 * sizeof(GLuint));
	m_render.draw<GL_ELEMENTS>(6, m_VertexArray);

	m_IndexBuffer.UnBind();
	m_VertexArray.UnBind();
}

GLvoid Sprite::draw(glm::vec3 position, glm::vec3 size, const GLuint frame_id, const GLfloat rotation, const GLint layer)
{
	if (m_last_frame_id != frame_id)
	{
		m_last_frame_id = frame_id;
		const FramesDescriptions& currentFrameDescription = m_frames_descriptions[frame_id];

		const GLfloat textureCoords[] = {
			currentFrameDescription.m_leftBottom.x, currentFrameDescription.m_leftBottom.y,
			currentFrameDescription.m_leftBottom.x, currentFrameDescription.m_topRight.y,
			currentFrameDescription.m_topRight.x, currentFrameDescription.m_topRight.y,
			currentFrameDescription.m_topRight.x, currentFrameDescription.m_leftBottom.y,
		};
		m_textureBuffer.update(textureCoords, 2 * 4 * sizeof(GLfloat));
	}

	m_shader_ptr->Bind();
	glm::mat4 model = glm::mat4(1.0f);
	m_shader_ptr->translate(model, position);
	m_shader_ptr->scale(model, size);
	m_shader_ptr->rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));

	m_shader_ptr->SetMatrixUniform4fv("model", model);
	m_shader_ptr->SetUniform1i("layer", layer);

	m_texture_ptr->Bind(0);
	m_render.draw<GL_ELEMENTS>(6, m_VertexArray);

}

GLvoid Sprite::InsertFrames(std::vector<FramesDescriptions> framesDescriptions)
{
	m_frames_descriptions = std::move(framesDescriptions);
}

GLdouble Sprite::getFrameDuration(const GLuint frame_id) const
{
	return m_frames_descriptions[frame_id].duration;
}

GLuint Sprite::getFramesCount() const
{
	return m_frames_descriptions.size();
}
