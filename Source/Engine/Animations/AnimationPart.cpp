#include "AnimationPart.h"

#include "SpriterPlusPlus/CCAnimationNode.h"

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
	this->trackedChildren = std::vector<cocos2d::Node*>();

	// Detach the spriter animation part from the timeline such that it is entirely in the user's control
	this->spriterAnimationPart->toggleTimelineCanUpdate(false);

	this->rotation = this->spriterAnimationPart->getAngle();
}

void AnimationPart::addSprite(std::string spriteResource)
{
	this->spriterAnimationPart->setImage(new SpriterEngine::ImageFile(spriteResource, SpriterEngine::point()));
}

void AnimationPart::addTrackedChild(Node* child)
{
	// We create a wrapper such that the passed 'child' argument can still be manipulated by the caller independently of this class
	// Example) Caller sets the passed 'child' argument's rotation to 180 deg. In this classes update loop, the tracked child's rotation will not overwrite this
	Node* wrapper = Node::create();

	this->trackedChildren.push_back(wrapper);
	wrapper->addChild(child);
	this->addChild(wrapper);
}

void AnimationPart::setAngle(float rotation)
{
	this->spriterAnimationPart->setAngle(rotation);
}

void AnimationPart::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void AnimationPart::update(float dt)
{
	super::update(dt);

	Vec2 position = Vec2(this->spriterAnimationPart->getPosition().x, -this->spriterAnimationPart->getPosition().y);
	float rotation = this->spriterAnimationPart->getAngle();

	for (auto it = this->trackedChildren.begin(); it != this->trackedChildren.end(); it++)
	{
		Node* child = *it;

		child->setRotation(rotation);
		child->setPosition(position);
	}
}
