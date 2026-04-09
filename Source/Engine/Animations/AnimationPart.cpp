#include "AnimationPart.h"

#include <cmath>
#include <map>

#include <spriter2dx/AnimationNode.h>

#include "2d/CCActionInstant.h"
#include "2d/CCActionInterval.h"
#include "2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Animations/Spriter/SpriterAnimationPart.h"
#include "Engine/Utils/GameUtils.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

AnimationPart* AnimationPart::create(SpriterEngine::EntityInstance* entity, std::string partName)
{
	AnimationPart* instance = new AnimationPart(entity, partName);

	instance->autorelease();

	return instance;
}

AnimationPart* AnimationPart::create(SpriterAnimationPart* spriterAnimationPart)
{
	AnimationPart* instance = new AnimationPart(spriterAnimationPart);

	instance->autorelease();

	return instance;
}

AnimationPart::AnimationPart(SpriterEngine::EntityInstance* entity, std::string partName)
{
	this->entity = entity;
	this->spriterAnimationPart = this->entity == nullptr ? nullptr : this->entity->getObjectInstance(partName);
	this->trackingContainer = Node::create();
	this->ghostContainer = Node::create();
	this->ghostSprite = this->spriterAnimationPart == nullptr ? nullptr : Sprite::create(this->spriterAnimationPart->getImage() == nullptr ? UIResources::EmptyImage : this->spriterAnimationPart->getImage()->path());
	this->originalPath = "";
	this->lastKnownAnim = "";

	if (this->trackingContainer != nullptr)
	{
		this->addChild(this->trackingContainer);
	}

	if (this->ghostContainer != nullptr)
	{
		this->addChild(this->ghostContainer);
	}

	if (this->ghostSprite != nullptr)
	{
		this->ghostSprite->setColor(Color3B::BLUE);
		this->ghostSprite->setVisible(false);
	}

	if (this->spriterAnimationPart != nullptr)
	{
		this->rotation = float(this->spriterAnimationPart->getAngle());

		if (this->spriterAnimationPart->getImage() != nullptr)
		{
			this->originalPath = this->spriterAnimationPart->getImage()->path();
		}
	}

	if (this->ghostSprite != nullptr)
	{
		this->ghostContainer->addChild(this->ghostSprite);
	}
}

AnimationPart::AnimationPart(SpriterAnimationPart* spriterAnimationPart)
{
	this->spriterAnimationPartNew = spriterAnimationPart;
	this->spriterAnimationPart = nullptr;
	this->entity = nullptr;
	this->trackingContainer = Node::create();
	this->ghostContainer = Node::create();
	this->ghostSprite = nullptr;
	this->originalPath = this->spriterAnimationPartNew == nullptr ? "" : this->spriterAnimationPartNew->getSpriteResource();
	this->lastKnownAnim = "";

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
	if (this->spriterAnimationPartNew != nullptr)
	{
		this->spriterAnimationPartNew->setTimelineCanUpdate(true);
		return;
	}

	if (this->spriterAnimationPart == nullptr)
	{
		return;
	}

	this->spriterAnimationPart->toggleTimelineCanUpdate(true);
}

void AnimationPart::detachFromTimeline()
{
	if (this->spriterAnimationPartNew != nullptr)
	{
		this->spriterAnimationPartNew->setTimelineCanUpdate(false);
		return;
	}

	if (this->spriterAnimationPart == nullptr)
	{
		return;
	}

	// Detach the spriter animation part from the timeline such that it is entirely in the user's control
	this->spriterAnimationPart->toggleTimelineCanUpdate(false);
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
	if (replacement == nullptr || (this->spriterAnimationPart == nullptr && this->spriterAnimationPartNew == nullptr))
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
			if (this->spriterAnimationPartNew != nullptr)
			{
				this->spriterAnimationPartNew->setAlphaOverride(-1.0f);
			}
			else if (this->spriterAnimationPart != nullptr)
			{
				this->spriterAnimationPart->setAlphaOverride(-1.0f);
			}
		}),
		nullptr
	));
}

std::string AnimationPart::getSpriteResource()
{
	return this->originalPath;
}

void AnimationPart::replaceSprite(std::string spriteResource)
{
	if (this->spriterAnimationPartNew != nullptr)
	{
		this->spriterAnimationPartNew->setSpriteResource(spriteResource);
		return;
	}

	if (this->spriterAnimationPart == nullptr || this->spriterAnimationPart->getImage() == nullptr)
	{
		return;
	}

	this->spriterAnimationPart->getImage()->setPath(spriteResource);
}

void AnimationPart::restoreSprite()
{
	if (this->spriterAnimationPartNew != nullptr)
	{
		this->spriterAnimationPartNew->restoreSpriteResource();
		return;
	}

	if (this->spriterAnimationPart == nullptr || this->spriterAnimationPart->getImage() == nullptr)
	{
		return;
	}
	
	this->spriterAnimationPart->getImage()->setPath(this->originalPath);
}

float AnimationPart::getRotationSpriter()
{
	if (this->spriterAnimationPartNew != nullptr)
	{
		float rotation = std::fmod(this->spriterAnimationPartNew->getRotation(), 360.0f);

		if (rotation > 180.0f)
		{
			rotation -= 360.0f;
		}

		return -rotation * float(M_PI) / 180.0f;
	}

	if (this->spriterAnimationPart != nullptr)
	{
		return float(this->spriterAnimationPart->getAngle());
	}

	return 0.0f;
}

void AnimationPart::setRotationSpriter(float rotation)
{
	this->detachFromTimeline();

	if (this->spriterAnimationPartNew != nullptr)
	{
		this->spriterAnimationPartNew->setRotation(-rotation * 180.0f / float(M_PI));
		return;
	}

	if (this->spriterAnimationPart != nullptr)
	{
		this->spriterAnimationPart->setAngle(rotation);
	}
}

void AnimationPart::setRotation(float rotation)
{
	this->detachFromTimeline();

	if (this->spriterAnimationPartNew != nullptr)
	{
		this->spriterAnimationPartNew->setRotation(rotation);
		return;
	}

	if (this->spriterAnimationPart != nullptr)
	{
		this->spriterAnimationPart->setAngle(-rotation / 180.0f * M_PI);
	}
}

void AnimationPart::setOffset(Vec2 offset)
{
	this->currentOffset = offset;

	if (this->spriterAnimationPartNew != nullptr)
	{
		// The new runtime already applies the legacy inner-sprite compatibility layout directly.
		// Keep gameplay equipment offsets in their authored Cocos (x, y) order here.
		this->spriterAnimationPartNew->setAnimationOffset(offset);
		return;
	}

	if (this->spriterAnimationPart != nullptr)
	{	
		// Flipped x/y for some reason
		this->spriterAnimationPart->setOffset(SpriterEngine::point(offset.y, offset.x));
	}
}

void AnimationPart::restoreOffset()
{
	this->currentOffset = Vec2::ZERO;

	if (this->spriterAnimationPartNew != nullptr)
	{
		this->spriterAnimationPartNew->clearAnimationOffset();
		return;
	}

	if (this->spriterAnimationPart != nullptr)
	{	
		this->spriterAnimationPart->setOffset(SpriterEngine::point(0.0f, 0.0f));
	}
}

void AnimationPart::setOpacity(GLubyte opacity)
{
	if (this->spriterAnimationPartNew != nullptr)
	{
		this->spriterAnimationPartNew->setAlphaOverride(float(opacity) / 255.0f);
		return;
	}

	if (this->spriterAnimationPart != nullptr)
	{
		this->spriterAnimationPart->setAlphaOverride((float)opacity / 255.0f);
	}
}

GLubyte AnimationPart::getOpacity() const
{
	if (this->spriterAnimationPartNew != nullptr)
	{
		float alphaOverride = this->spriterAnimationPartNew->getAlphaOverride();

		return alphaOverride >= 0.0f ? GLubyte(alphaOverride * 255.0f) : this->spriterAnimationPartNew->getDisplayedOpacity();
	}

	if (this->spriterAnimationPart != nullptr)
	{
		return (GLubyte)(this->spriterAnimationPart->getAlphaOverride() * 255.0f);
	}
	
	return 0;
}

CSize AnimationPart::getSpriteSize()
{
	if (this->spriterAnimationPartNew != nullptr)
	{
		return this->spriterAnimationPartNew->getSpriteSize();
	}

	return this->ghostSprite == nullptr ? CSize::ZERO : this->ghostSprite->getContentSize();
}

void AnimationPart::setVisible(bool visible)
{
	static const float ClearOverride = -1.0f;

	if (this->spriterAnimationPartNew != nullptr)
	{
		this->spriterAnimationPartNew->setVisible(visible);
		return;
	}

	if (this->spriterAnimationPart != nullptr)
	{
		this->spriterAnimationPart->setAlphaOverride(visible ? 1.0f : ClearOverride);
	}
}

	Vec2 AnimationPart::getOffset() const
	{
		return this->currentOffset;
	}

void AnimationPart::updateTrackedAttributes()
{
	if (this->ghostSprite == nullptr)
	{
		if (this->spriterAnimationPartNew == nullptr)
		{
			return;
		}
	}

	SmartAnimationNode* parent = dynamic_cast<SmartAnimationNode*>(this->getParent());

	if (this->spriterAnimationPartNew != nullptr)
	{
		const float angle = this->spriterAnimationPartNew->getResolvedAnimationRotation();
		const Vec2 position = this->spriterAnimationPartNew->getResolvedAnimationPosition();
		const Vec2 anchor = this->spriterAnimationPartNew->getAnimationAnchorPoint();
		const Vec2 animationOffset = this->spriterAnimationPartNew->getAnimationOffset();

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

		if (this->ghostSprite != nullptr)
		{
			const std::string currentSpriteResource = this->spriterAnimationPartNew->getSpriteResource();
			const bool usesCompatibilityLayout = currentSpriteResource != this->originalPath || animationOffset != Vec2::ZERO;
			const Vec2 resolvedScale = this->spriterAnimationPartNew->getResolvedAnimationScale();

			if (!currentSpriteResource.empty() && currentSpriteResource != this->ghostSprite->getResourceName())
			{
				this->ghostSprite->setTexture(currentSpriteResource);
			}

			if (this->ghostContainer != nullptr)
			{
				this->ghostContainer->setScale(resolvedScale.x, resolvedScale.y);
			}

			if (this->ghostContainer != nullptr && usesCompatibilityLayout)
			{
				this->ghostContainer->setContentSize(this->ghostSprite->getContentSize());
				this->ghostContainer->setAnchorPoint(anchor);
				this->ghostContainer->setPosition(Vec2::ZERO);
				this->ghostSprite->setAnchorPoint(Vec2::ZERO);
				this->ghostSprite->setPosition(animationOffset);
				this->ghostSprite->setFlippedX(false);
			}
			else
			{
				if (this->ghostContainer != nullptr)
				{
					this->ghostContainer->setContentSize(CSize::ZERO);
					this->ghostContainer->setAnchorPoint(Vec2::ZERO);
					this->ghostContainer->setPosition(Vec2::ZERO);
				}

				this->ghostSprite->setAnchorPoint(anchor);
				this->ghostSprite->setPosition(animationOffset);
				this->ghostSprite->setFlippedX(false);
			}
		}
		else if (this->ghostContainer != nullptr)
		{
			this->ghostContainer->setContentSize(CSize::ZERO);
			this->ghostContainer->setAnchorPoint(Vec2::ZERO);
			this->ghostContainer->setPosition(Vec2::ZERO);
			this->ghostContainer->setScale(1.0f);
		}

		return;
	}

	const float angle = float(this->spriterAnimationPart->getAngle());
	const Vec2 position = Vec2(float(this->spriterAnimationPart->getPosition().x), -float(this->spriterAnimationPart->getPosition().y));
	const Vec2 anchor = Vec2(float(this->spriterAnimationPart->getPivot().x), float(this->spriterAnimationPart->getPivot().y));

	// Keep the wrapper at the part pivot in legacy animation space.
	super::setRotation(angle * 180.0f / float(M_PI));
	super::setPosition(position);
	super::setAnchorPoint(Vec2::ZERO);
	if (this->trackingContainer != nullptr)
	{
		this->trackingContainer->setContentSize(CSize::ZERO);
		this->trackingContainer->setAnchorPoint(Vec2::ZERO);
		this->trackingContainer->setPosition(Vec2::ZERO);
		this->trackingContainer->setScale(1.0f);
	}
	this->ghostContainer->setContentSize(CSize::ZERO);
	this->ghostContainer->setAnchorPoint(Vec2::ZERO);
	this->ghostContainer->setPosition(Vec2::ZERO);
	this->ghostContainer->setScale(1.0f);

	this->ghostSprite->setAnchorPoint(anchor);
	this->ghostSprite->setPosition(Vec2::ZERO);

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
