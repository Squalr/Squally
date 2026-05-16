#include "AnimationPart.h"

#include <cmath>
#include "2d/CCActionInstant.h"
#include "2d/CCActionInterval.h"
#include "2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Animations/Spriter/SpriterAnimationPart.h"
#include "Engine/Utils/GameUtils.h"

using namespace cocos2d;

AnimationPart* AnimationPart::create(SpriterAnimationPart* spriterAnimationPart)
{
	AnimationPart* instance = new AnimationPart(spriterAnimationPart);

	instance->autorelease();

	return instance;
}

AnimationPart::AnimationPart(SpriterAnimationPart* spriterAnimationPart)
{
	this->spriterAnimationPart = spriterAnimationPart;
	this->trackingContainer = Node::create();
	this->ghostContainer = Node::create();
	this->ghostSprite = nullptr;
	this->originalPath = this->spriterAnimationPart == nullptr ? "" : this->spriterAnimationPart->getSpriteResource();

	if (this->trackingContainer != nullptr)
	{
		this->addChild(this->trackingContainer);
	}

	if (this->ghostContainer != nullptr)
	{
		this->addChild(this->ghostContainer);
	}

	if (!this->originalPath.empty())
	{
		this->ghostSprite = Sprite::create(this->originalPath);

		if (this->ghostSprite != nullptr)
		{
			this->ghostSprite->setColor(Color3B::BLUE);
			this->ghostSprite->setVisible(false);
			this->ghostContainer->addChild(this->ghostSprite);
		}
	}
}

AnimationPart::~AnimationPart()
{
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

void AnimationPart::visit(cocos2d::Renderer *renderer, const cocos2d::Mat4& parentTransform, uint32_t parentFlags)
{
	this->updateTrackedAttributes();

	super::visit(renderer, parentTransform, parentFlags);
}

void AnimationPart::reattachToTimeline()
{
	if (this->spriterAnimationPart != nullptr)
	{
		this->spriterAnimationPart->setTimelineCanUpdate(true);
	}
}

void AnimationPart::detachFromTimeline()
{
	if (this->spriterAnimationPart != nullptr)
	{
		this->spriterAnimationPart->setTimelineCanUpdate(false);
	}
}

void AnimationPart::removeTrackingObject(Node* trackedObject)
{
	if (trackedObject == nullptr)
	{
		return;
	}

	if (std::find(this->trackedObjects.begin(), this->trackedObjects.end(), trackedObject) != this->trackedObjects.end())
	{
		if (trackedObject->getParent() != nullptr)
		{
			trackedObject->removeFromParent();
		}

		this->trackedObjects.erase(std::remove(this->trackedObjects.begin(), this->trackedObjects.end(), trackedObject), this->trackedObjects.end());
	}
}

void AnimationPart::addTrackingObject(Node* trackedObject)
{
	if (trackedObject == nullptr)
	{
		return;
	}

	Node* trackingParent = this->trackingContainer != nullptr ? this->trackingContainer : static_cast<Node*>(this);
	trackingParent->addChild(trackedObject);

	this->trackedObjects.push_back(trackedObject);
}

void AnimationPart::replaceWithObject(Node* replacement, float disappearDuration, float fadeInDuration)
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
			if (this->spriterAnimationPart != nullptr)
			{
				this->spriterAnimationPart->setAlphaOverride(-1.0f);
			}
		}),
		nullptr
	));
}

std::string AnimationPart::getSpriteResource()
{
	if (this->spriterAnimationPart != nullptr)
	{
		std::string currentSpriteResource = this->spriterAnimationPart->getSpriteResource();

		if (!currentSpriteResource.empty())
		{
			return currentSpriteResource;
		}
	}

	return this->originalPath;
}

void AnimationPart::replaceSprite(std::string spriteResource)
{
	if (this->spriterAnimationPart == nullptr)
	{
		return;
	}

	this->spriterAnimationPart->setSpriteResourceOverride(spriteResource);
}

void AnimationPart::restoreSprite()
{
	if (this->spriterAnimationPart == nullptr)
	{
		return;
	}
	
	this->spriterAnimationPart->restoreSpriteResource();
}

float AnimationPart::getRotationSpriter()
{
	if (this->spriterAnimationPart != nullptr)
	{
		float rotation = std::fmod(this->spriterAnimationPart->getRotation(), 360.0f);

		if (rotation > 180.0f)
		{
			rotation -= 360.0f;
		}

		return -rotation * float(M_PI) / 180.0f;
	}

	return 0.0f;
}

void AnimationPart::setRotationSpriter(float rotation)
{
	this->detachFromTimeline();

	if (this->spriterAnimationPart != nullptr)
	{
		this->spriterAnimationPart->setRotation(-rotation * 180.0f / float(M_PI));
		return;
	}
}

void AnimationPart::setRotation(float rotation)
{
	this->detachFromTimeline();

	if (this->spriterAnimationPart != nullptr)
	{
		this->spriterAnimationPart->setRotation(rotation);
		return;
	}
}

void AnimationPart::setOffset(Vec2 offset)
{
	this->currentOffset = offset;

	if (this->spriterAnimationPart != nullptr)
	{
		// The new runtime already applies the legacy inner-sprite compatibility layout directly.
		// Keep gameplay equipment offsets in their authored Cocos (x, y) order here.
		this->spriterAnimationPart->setAnimationOffset(offset);
	}
}

void AnimationPart::restoreOffset()
{
	this->currentOffset = Vec2::ZERO;

	if (this->spriterAnimationPart != nullptr)
	{
		this->spriterAnimationPart->clearAnimationOffset();
	}
}

void AnimationPart::setOpacity(GLubyte opacity)
{
	if (this->spriterAnimationPart != nullptr)
	{
		this->spriterAnimationPart->setAlphaOverride(float(opacity) / 255.0f);
	}
}

GLubyte AnimationPart::getOpacity() const
{
	if (this->spriterAnimationPart != nullptr)
	{
		float alphaOverride = this->spriterAnimationPart->getAlphaOverride();

		return alphaOverride >= 0.0f ? GLubyte(alphaOverride * 255.0f) : this->spriterAnimationPart->getDisplayedOpacity();
	}
	
	return 0;
}

CSize AnimationPart::getSpriteSize()
{
	if (this->spriterAnimationPart != nullptr)
	{
		return this->spriterAnimationPart->getSpriteSize();
	}

	return this->ghostSprite == nullptr ? CSize::ZERO : this->ghostSprite->getContentSize();
}

void AnimationPart::setVisible(bool visible)
{
	if (this->spriterAnimationPart != nullptr)
	{
		this->spriterAnimationPart->setVisible(visible);
	}
}

Vec2 AnimationPart::getOffset() const
{
	return this->currentOffset;
}

void AnimationPart::updateTrackedAttributes()
{
	if (this->spriterAnimationPart == nullptr)
	{
		return;
	}

	SmartAnimationNode* parent = dynamic_cast<SmartAnimationNode*>(this->getParent());

	const float angle = this->spriterAnimationPart->getResolvedAnimationRotation();
	const Vec2 position = this->spriterAnimationPart->getResolvedAnimationPosition();
	const Vec2 anchor = this->spriterAnimationPart->getAnimationAnchorPoint();
	const Vec2 animationOffset = this->spriterAnimationPart->getAnimationOffset();
	const Vec2 resolvedScale = this->spriterAnimationPart->getResolvedAnimationScale();
	const std::string currentSpriteResource = this->spriterAnimationPart->getSpriteResource();

	// Keep the wrapper at the part pivot in local animation space.
	super::setRotation(angle);
	super::setPosition(position);
	super::setAnchorPoint(Vec2::ZERO);

	if (this->trackingContainer != nullptr)
	{
		this->trackingContainer->setContentSize(CSize::ZERO);
		this->trackingContainer->setAnchorPoint(Vec2::ZERO);
		this->trackingContainer->setPosition(Vec2::ZERO);
		this->trackingContainer->setScale(1.0f);
	}

	if (this->ghostSprite != nullptr && !currentSpriteResource.empty() && currentSpriteResource != this->ghostSprite->getResourceName())
	{
		this->ghostSprite->setTexture(currentSpriteResource);
	}

	if (this->ghostContainer != nullptr)
	{
		this->ghostContainer->setScale(resolvedScale.x, resolvedScale.y);
		this->ghostContainer->setContentSize(CSize::ZERO);
		this->ghostContainer->setAnchorPoint(Vec2::ZERO);
		this->ghostContainer->setPosition(Vec2::ZERO);
	}

	if (this->ghostSprite != nullptr)
	{
		this->ghostSprite->setAnchorPoint(anchor);
		this->ghostSprite->setPosition(animationOffset);
		this->ghostSprite->setFlippedX(false);
	}

	if (this->ghostSprite == nullptr || this->ghostContainer == nullptr)
	{
		return;
	}

	if (parent != nullptr)
	{
		this->ghostSprite->setFlippedX(parent->getFlippedX());
	}
}

void AnimationPart::onDeveloperModeEnable(int debugLevel)
{
	super::onDeveloperModeEnable(debugLevel);

	if (this->ghostSprite != nullptr)
	{
		this->ghostSprite->setVisible(debugLevel >= 2);
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
