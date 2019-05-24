#include "AnimationPart.h"

#include <spriter2dx/AnimationNode.h>

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Utils/GameUtils.h"

#include "Resources/UIResources.h"

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
	this->ghostSprite = this->spriterAnimationPart == nullptr ? nullptr : Sprite::create(this->spriterAnimationPart->getImage() == nullptr ? UIResources::EmptyImage : this->spriterAnimationPart->getImage()->path());

	if (this->ghostSprite != nullptr)
	{
		this->ghostSprite->setColor(Color3B::BLUE);
		this->ghostSprite->setVisible(false);
	}

	if (this->spriterAnimationPart != nullptr)
	{
		this->rotation = float(this->spriterAnimationPart->getAngle());
	}

	if (this->ghostSprite != nullptr)
	{
		this->addChild(this->ghostSprite);
	}
}

void AnimationPart::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void AnimationPart::update(float dt)
{
	super::update(dt);

	this->updateTrackedAttributes();
}

void AnimationPart::detachFromTimeline()
{
	if (this->spriterAnimationPart == nullptr)
	{
		return;
	}

	// Detach the spriter animation part from the timeline such that it is entirely in the user's control
	this->spriterAnimationPart->toggleTimelineCanUpdate(false);
}

void AnimationPart::replaceWithObject(cocos2d::Node* replacement, float disappearDuration, float fadeInDuration)
{
	if (replacement == nullptr || this->spriterAnimationPart == nullptr)
	{
		return;
	}

	this->setOpacity(0);
	replacement->setRotation(this->getRotation());
	replacement->setPosition(GameUtils::getWorldCoords(this));

	this->runAction(Sequence::create(
		DelayTime::create(disappearDuration),
		FadeTo::create(fadeInDuration, 255),
		CallFunc::create([=]()
		{
			// -1 means to use whatever value is on the timeline (no longer overriding)
			this->spriterAnimationPart->setAlphaOverride(-1.0f);
		}),
		nullptr
	));
}

void AnimationPart::replaceSprite(std::string spriteResource)
{
	if (this->spriterAnimationPart == nullptr || this->spriterAnimationPart->getImage() == nullptr)
	{
		return;
	}

	this->spriterAnimationPart->getImage()->setPath(spriteResource);
}

void AnimationPart::setRotation(float rotation)
{
	this->detachFromTimeline();

	if (this->spriterAnimationPart != nullptr)
	{
		this->spriterAnimationPart->setAngle(rotation / 180.0f * M_PI);
	}

	this->updateTrackedAttributes();
}

void AnimationPart::setOffset(Vec2 offset)
{
	if (this->spriterAnimationPart != nullptr)
	{
		this->spriterAnimationPart->setOffset(SpriterEngine::point(offset.x, offset.y));
	}
}

void AnimationPart::setOpacity(GLubyte opacity)
{
	if (this->spriterAnimationPart != nullptr)
	{
		this->spriterAnimationPart->setAlphaOverride((float)opacity / 255.0f);
	}
}

GLubyte AnimationPart::getOpacity() const
{
	if (this->spriterAnimationPart != nullptr)
	{
		return (GLubyte)(this->spriterAnimationPart->getAlphaOverride() * 255.0f);
	}
	
	return 0;
}

void AnimationPart::setVisible(bool visible)
{
	static const float ClearOverride = -1.0f;

	if (this->spriterAnimationPart != nullptr)
	{
		this->spriterAnimationPart->setAlphaOverride(visible ? 1.0f : ClearOverride);
	}
}

void AnimationPart::updateTrackedAttributes()
{
	if (this->ghostSprite == nullptr)
	{
		return;
	}

	SmartAnimationNode* parent = dynamic_cast<SmartAnimationNode*>(this->getParent());
	this->ghostSprite->setPosition(Vec2(this->ghostSprite->getContentSize().width / 2.0f, this->ghostSprite->getContentSize().height / 2.0f));

	if (parent != nullptr)
	{
		this->ghostSprite->setFlippedX(parent->getFlippedX());

		if (!parent->getFlippedX())
		{
			// TODO: This logic is wrong and only results in quasi-accuracy (Enter debug mode and watch the ghost sprites visually to see the bug)
			this->ghostSprite->setPositionX(this->ghostSprite->getPositionX() * 2.0f);
		}
	}

	Vec3 spriteCoords = GameUtils::getWorldCoords3D(this->ghostSprite);
	Vec3 thisCords = GameUtils::getWorldCoords3D(this);
	Vec3 delta = thisCords - spriteCoords;

	// In order to make the game think that this AnimationPart class is the Spriter object, we need to keep certain things in sync
	super::setRotation(float(this->spriterAnimationPart->getAngle()) * 180.0f / float(M_PI));
	super::setPosition(Vec2(float(this->spriterAnimationPart->getPosition().x), -float(this->spriterAnimationPart->getPosition().y)) - Vec2(delta.x, delta.y));
	super::setAnchorPoint(Vec2(float(this->spriterAnimationPart->getPivot().x), float(this->spriterAnimationPart->getPivot().y)));

	this->ghostSprite->setPosition(Vec2::ZERO);
}

void AnimationPart::onDeveloperModeEnable()
{
	super::onDeveloperModeEnable();

	if (this->ghostSprite != nullptr)
	{
		this->ghostSprite->setVisible(true);
	}
}

void AnimationPart::onDeveloperModeDisable()
{
	super::onDeveloperModeDisable();

	if (this->ghostSprite != nullptr)
	{
		this->ghostSprite->setVisible(false);
	}
}
