#include "render/SpriteAnimation.hpp"

SpriteAnimation::SpriteAnimation(std::shared_ptr<Sprite> sprite_ptr):
	m_sprite_ptr(std::move(sprite_ptr)), CurrentFrame(0), m_currentAnimationTime(0),
	m_totalDuration(0), m_currentFrameDuration(m_sprite_ptr->getFrameDuration(0))
{
	for (GLuint currentFrameID = 0; currentFrameID < m_sprite_ptr->getFramesCount(); ++currentFrameID)
	{
		m_totalDuration += m_sprite_ptr->getFrameDuration(currentFrameID);
	}
}

GLvoid SpriteAnimation::update(const GLdouble delta)
{
	m_currentAnimationTime += delta;
	while (m_currentAnimationTime >= m_currentFrameDuration)
	{
		m_currentAnimationTime -= m_currentFrameDuration;
		++CurrentFrame;
		if (CurrentFrame == m_sprite_ptr->getFramesCount())
			CurrentFrame = 0;
		m_currentFrameDuration = m_sprite_ptr->getFrameDuration(CurrentFrame);
	}
}

GLvoid SpriteAnimation::reset()
{
	m_currentAnimationTime = 0;
	CurrentFrame = 0;
	m_currentFrameDuration = m_sprite_ptr->getFrameDuration(0);
}
