#include "AnimationPart.h"

#include <spriter2dx/AnimationNode.h>

using namespace cocos2d;

AnimationPart* AnimationPart::create(SpriterEngine::EntityInstance* entity, std::string partName)
{
	AnimationPart* instance = new AnimationPart(entity, partName);

	instance->autorelease();

	return instance;
}

AnimationPart::AnimationPart(SpriterEngine::EntityInstance* entity, std::string partName)
{
	this->spriterAnimationPart = entity->getObjectInstance(partName);

	this->rotation = this->spriterAnimationPart->getAngle();
}

void AnimationPart::detachFromTimeline()
{
	// Detach the spriter animation part from the timeline such that it is entirely in the user's control
	this->spriterAnimationPart->toggleTimelineCanUpdate(false);
}

void AnimationPart::replaceSprite(std::string spriteResource)
{
	this->spriterAnimationPart->getImage()->setPath(spriteResource);
}

void AnimationPart::setAngle(float rotation)
{
	this->detachFromTimeline();

	this->spriterAnimationPart->setAngle(rotation);
}

void AnimationPart::setOffset(Vec2 offset)
{
	this->spriterAnimationPart->setOffset(SpriterEngine::point(offset.x, offset.y));
}
