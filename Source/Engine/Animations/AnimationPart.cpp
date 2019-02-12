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

void AnimationPart::setRotation(float rotation)
{
	this->detachFromTimeline();
	this->spriterAnimationPart->setAngle(rotation);
}

void AnimationPart::setOffset(Vec2 offset)
{
	this->spriterAnimationPart->setOffset(SpriterEngine::point(offset.x, offset.y));
}

void AnimationPart::setOpacity(GLubyte opacity)
{
	this->spriterAnimationPart->setAlphaOverride((float)opacity / 255.0f);
}

void AnimationPart::setVisible(bool visible)
{
	static const float ClearOverride = -1.0f;

	this->spriterAnimationPart->setAlphaOverride(visible ? 1.0f : ClearOverride);
}

const cocos2d::Vec2& AnimationPart::getPosition() const
{
	return Vec2(this->spriterAnimationPart->getPosition().x, this->spriterAnimationPart->getPosition().y);
}

Vec3 AnimationPart::getPosition3D() const
{
	return Vec3(this->spriterAnimationPart->getPosition().x, this->spriterAnimationPart->getPosition().y, 0.0f);
}

float AnimationPart::getRotation() const
{
	return this->spriterAnimationPart->getAngle();
}