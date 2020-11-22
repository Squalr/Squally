#include "AnimationPart.h"

using namespace cocos2d;

SpriterAnimation* SpriterAnimation::create(std::string animationResource)
{
	SpriterAnimation* instance = new SpriterAnimation(animationResource);

	instance->autorelease();

	return instance;
}

SpriterAnimation::SpriterAnimation(std::string animationResource)
{
}
