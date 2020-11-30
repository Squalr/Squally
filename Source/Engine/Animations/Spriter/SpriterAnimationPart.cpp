#include "SpriterAnimationPart.h"

using namespace cocos2d;

SpriterAnimationPart* SpriterAnimationPart::create()
{
	SpriterAnimationPart* instance = new SpriterAnimationPart();

	instance->autorelease();

	return instance;
}

SpriterAnimationPart::SpriterAnimationPart()
{
}

SpriterAnimationPart::~SpriterAnimationPart()
{
}
