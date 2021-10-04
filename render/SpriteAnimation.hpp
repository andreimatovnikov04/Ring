#ifndef _SPRITEANIMATION_HPP_
#define _SPRITEANIMATION_HPP_

#include "Sprite.hpp"

class SpriteAnimation
{
public:
	SpriteAnimation(std::shared_ptr<Sprite> sprite_ptr);

	GLvoid update(const GLdouble delta);
	GLvoid reset();

	inline GLuint GetCurrentFrame() const { return CurrentFrame; }
	inline GLdouble GetTotalDuration() const { return m_totalDuration;}

private:
	std::shared_ptr <Sprite> m_sprite_ptr;
	GLuint CurrentFrame;
	GLdouble m_currentFrameDuration;
	GLdouble m_currentAnimationTime;
	GLdouble m_totalDuration;
};
#endif