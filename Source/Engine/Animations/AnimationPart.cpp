#include "AnimationPart.h"

#include <algorithm>
#include <cmath>

#include <spriter2dx/AnimationNode.h>

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Animations/Spriter/SpriterAnimationNode.h"
#include "Engine/Animations/Spriter/SpriterAnimationPart.h"
#include "Engine/Animations/Spriter/SpriterAnimationSprite.h"
#include "Engine/Utils/GameUtils.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

namespace
{
	class LegacyAnimationPartControlTarget : public AnimationPart::ControlTarget
	{
	public:
		LegacyAnimationPartControlTarget(SpriterEngine::EntityInstance* entity, const std::string& partName)
		{
			this->spriterAnimationPart = entity == nullptr ? nullptr : entity->getObjectInstance(partName);
		}

		bool isValid() const override
		{
			return this->spriterAnimationPart != nullptr;
		}

		void setTimelineCanUpdate(bool canUpdate) override
		{
			if (this->spriterAnimationPart != nullptr)
			{
				this->spriterAnimationPart->toggleTimelineCanUpdate(canUpdate);
			}
		}

		std::string getSpritePath() const override
		{
			if (this->spriterAnimationPart == nullptr || this->spriterAnimationPart->getImage() == nullptr)
			{
				return "";
			}

			return this->spriterAnimationPart->getImage()->path();
		}

		void setSpritePath(const std::string& spritePath) override
		{
			if (this->spriterAnimationPart == nullptr || this->spriterAnimationPart->getImage() == nullptr)
			{
				return;
			}

			this->spriterAnimationPart->getImage()->setPath(spritePath);
		}

		CSize getSpriteSize() const override
		{
			if (this->spriterAnimationPart == nullptr || this->spriterAnimationPart->getImage() == nullptr)
			{
				return CSize::ZERO;
			}

			const std::string& spritePath = this->spriterAnimationPart->getImage()->path();
			Sprite* sprite = Sprite::create(spritePath);

			return sprite == nullptr ? CSize::ZERO : sprite->getContentSize();
		}

		float getAngleRadians() const override
		{
			if (this->spriterAnimationPart == nullptr)
			{
				return 0.0f;
			}

			return float(this->spriterAnimationPart->getAngle());
		}

		void setAngleRadians(float angleRadians) override
		{
			if (this->spriterAnimationPart != nullptr)
			{
				this->spriterAnimationPart->setAngle(angleRadians);
			}
		}

		void setOffset(const Vec2& offset) override
		{
			if (this->spriterAnimationPart != nullptr)
			{
				// Legacy spriter space stores x/y swapped relative to caller expectations.
				this->spriterAnimationPart->setOffset(SpriterEngine::point(offset.y, offset.x));
			}
		}

		void setAlphaOverride(float alphaOverride) override
		{
			if (this->spriterAnimationPart != nullptr)
			{
				this->spriterAnimationPart->setAlphaOverride(alphaOverride);
			}
		}

		float getAlphaOverride() const override
		{
			if (this->spriterAnimationPart == nullptr)
			{
				return -1.0f;
			}

			return float(this->spriterAnimationPart->getAlphaOverride());
		}

		Vec2 getPosition() const override
		{
			if (this->spriterAnimationPart == nullptr)
			{
				return Vec2::ZERO;
			}

			const auto& position = this->spriterAnimationPart->getPosition();
			return Vec2(float(position.x), -float(position.y));
		}

		Vec2 getPivot() const override
		{
			if (this->spriterAnimationPart == nullptr)
			{
				return Vec2::ZERO;
			}

			const auto& pivot = this->spriterAnimationPart->getPivot();
			return Vec2(float(pivot.x), float(pivot.y));
		}

	private:
		SpriterEngine::UniversalObjectInterface* spriterAnimationPart = nullptr;
	};

	class SpriterAnimationPartControlTarget : public AnimationPart::ControlTarget
	{
	public:
		SpriterAnimationPartControlTarget(SpriterAnimationNode* spriterAnimation, const std::string& partName)
		{
			this->part = spriterAnimation == nullptr ? nullptr : spriterAnimation->getPartByName(partName);
			this->sprite = dynamic_cast<SpriterAnimationSprite*>(this->part);
		}

		bool isValid() const override
		{
			return this->part != nullptr;
		}

		void setTimelineCanUpdate(bool canUpdate) override
		{
			if (this->part != nullptr)
			{
				this->part->setTimelineCanUpdate(canUpdate);
			}
		}

		std::string getSpritePath() const override
		{
			return this->sprite == nullptr ? "" : this->sprite->getSpriteResource();
		}

		void setSpritePath(const std::string& spritePath) override
		{
			if (this->sprite != nullptr)
			{
				this->sprite->setSpriteResource(spritePath);
			}
		}

		CSize getSpriteSize() const override
		{
			return this->sprite == nullptr ? CSize::ZERO : this->sprite->getSpriteSize();
		}

		float getAngleRadians() const override
		{
			if (this->part == nullptr)
			{
				return 0.0f;
			}

			return this->part->getRotation() * float(M_PI) / 180.0f;
		}

		void setAngleRadians(float angleRadians) override
		{
			if (this->part != nullptr)
			{
				this->part->setRotation(angleRadians * 180.0f / float(M_PI));
			}
		}

		void setOffset(const Vec2& offset) override
		{
			if (this->part != nullptr)
			{
				// Preserve legacy gameplay semantics where authored offsets map as y/x.
				this->part->setAnimationOffset(Vec2(offset.y, offset.x));
			}
		}

		void setAlphaOverride(float alphaOverride) override
		{
			if (this->part != nullptr)
			{
				this->part->setAlphaOverride(alphaOverride);
			}
		}

		float getAlphaOverride() const override
		{
			if (this->part == nullptr)
			{
				return -1.0f;
			}

			return this->part->getAlphaOverride();
		}

		Vec2 getPosition() const override
		{
			return this->part == nullptr ? Vec2::ZERO : this->part->getPosition();
		}

		Vec2 getPivot() const override
		{
			return this->part == nullptr ? Vec2::ZERO : this->part->getAnchorPoint();
		}

	private:
		SpriterAnimationPart* part = nullptr;
		SpriterAnimationSprite* sprite = nullptr;
	};
}

AnimationPart* AnimationPart::create(SpriterEngine::EntityInstance* entity, std::string partName)
{
	AnimationPart::ControlTarget* controlTarget = new LegacyAnimationPartControlTarget(entity, partName);

	if (!controlTarget->isValid())
	{
		delete controlTarget;
		return nullptr;
	}

	AnimationPart* instance = new AnimationPart(controlTarget);

	instance->autorelease();

	return instance;
}

AnimationPart* AnimationPart::create(SpriterAnimationNode* spriterAnimation, const std::string& partName)
{
	AnimationPart::ControlTarget* controlTarget = new SpriterAnimationPartControlTarget(spriterAnimation, partName);

	if (!controlTarget->isValid())
	{
		delete controlTarget;
		return nullptr;
	}

	AnimationPart* instance = new AnimationPart(controlTarget);

	instance->autorelease();

	return instance;
}

AnimationPart::AnimationPart(ControlTarget* controlTarget)
{
	this->controlTarget = controlTarget;
	this->originalPath = "";
	this->ghostSpritePath = "";
	this->lastKnownAnim = "";

	if (this->controlTarget != nullptr && this->controlTarget->isValid())
	{
		this->rotation = this->controlTarget->getAngleRadians();
		this->originalPath = this->controlTarget->getSpritePath();
		this->ghostSpritePath = this->originalPath;
	}

	this->ghostSprite = Sprite::create(this->ghostSpritePath.empty() ? UIResources::EmptyImage : this->ghostSpritePath);

	if (this->ghostSprite != nullptr)
	{
		this->ghostSprite->setColor(Color3B::BLUE);
		this->ghostSprite->setVisible(false);
		this->addChild(this->ghostSprite);
	}
}

AnimationPart::~AnimationPart()
{
	delete this->controlTarget;
	this->controlTarget = nullptr;
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
	if (this->controlTarget == nullptr)
	{
		return;
	}

	this->controlTarget->setTimelineCanUpdate(true);
}

void AnimationPart::detachFromTimeline()
{
	if (this->controlTarget == nullptr)
	{
		return;
	}

	this->controlTarget->setTimelineCanUpdate(false);
}

void AnimationPart::removeTrackingObject(Node* trackedObject)
{
	if (trackedObject == nullptr)
	{
		return;
	}

	if (std::find(this->trackedObjects.begin(), this->trackedObjects.end(), trackedObject) != this->trackedObjects.end())
	{
		this->removeChild(trackedObject);

		this->trackedObjects.erase(std::remove(this->trackedObjects.begin(), this->trackedObjects.end(), trackedObject), this->trackedObjects.end());
	}
}

void AnimationPart::addTrackingObject(Node* trackedObject)
{
	if (trackedObject == nullptr)
	{
		return;
	}

	this->addChild(trackedObject);

	this->trackedObjects.push_back(trackedObject);
}

void AnimationPart::replaceWithObject(Node* replacement, float disappearDuration, float fadeInDuration)
{
	if (replacement == nullptr || this->controlTarget == nullptr)
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
			this->controlTarget->setAlphaOverride(-1.0f);
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
	if (this->controlTarget == nullptr)
	{
		return;
	}

	this->controlTarget->setSpritePath(spriteResource);
}

void AnimationPart::restoreSprite()
{
	if (this->controlTarget == nullptr)
	{
		return;
	}

	this->controlTarget->setSpritePath(this->originalPath);
}

float AnimationPart::getRotationSpriter()
{
	if (this->controlTarget != nullptr)
	{
		return this->controlTarget->getAngleRadians();
	}

	return 0.0f;
}

void AnimationPart::setRotationSpriter(float rotation)
{
	this->detachFromTimeline();

	if (this->controlTarget != nullptr)
	{
		this->controlTarget->setAngleRadians(rotation);
	}
}

void AnimationPart::setRotation(float rotation)
{
	this->detachFromTimeline();

	if (this->controlTarget != nullptr)
	{
		this->controlTarget->setAngleRadians(-rotation / 180.0f * float(M_PI));
	}
}

void AnimationPart::setOffset(Vec2 offset)
{
	if (this->controlTarget != nullptr)
	{
		this->controlTarget->setOffset(offset);
	}
}

void AnimationPart::restoreOffset()
{
	if (this->controlTarget != nullptr)
	{
		this->controlTarget->setOffset(Vec2::ZERO);
	}
}

void AnimationPart::setOpacity(GLubyte opacity)
{
	if (this->controlTarget != nullptr)
	{
		this->controlTarget->setAlphaOverride(float(opacity) / 255.0f);
	}
}

GLubyte AnimationPart::getOpacity() const
{
	if (this->controlTarget != nullptr)
	{
		return GLubyte(this->controlTarget->getAlphaOverride() * 255.0f);
	}

	return 0;
}

CSize AnimationPart::getSpriteSize()
{
	if (this->controlTarget != nullptr)
	{
		CSize spriteSize = this->controlTarget->getSpriteSize();

		if (spriteSize.width != 0.0f || spriteSize.height != 0.0f)
		{
			return spriteSize;
		}
	}

	return this->ghostSprite == nullptr ? CSize::ZERO : this->ghostSprite->getContentSize();
}

void AnimationPart::setVisible(bool visible)
{
	if (this->controlTarget != nullptr)
	{
		static const float ClearOverride = -1.0f;
		this->controlTarget->setAlphaOverride(visible ? 1.0f : ClearOverride);
	}
}

void AnimationPart::updateTrackedAttributes()
{
	if (this->ghostSprite == nullptr || this->controlTarget == nullptr || !this->controlTarget->isValid())
	{
		return;
	}

	const std::string currentSpritePath = this->controlTarget->getSpritePath();

	if (currentSpritePath != this->ghostSpritePath && !currentSpritePath.empty())
	{
		this->ghostSpritePath = currentSpritePath;
		this->ghostSprite->initWithFile(this->ghostSpritePath);
	}

	SmartAnimationNode* parent = dynamic_cast<SmartAnimationNode*>(this->getParent());
	this->ghostSprite->setPosition(Vec2(this->ghostSprite->getContentSize().width / 2.0f, this->ghostSprite->getContentSize().height / 2.0f));

	if (parent != nullptr)
	{
		this->ghostSprite->setFlippedX(parent->getFlippedX());

		if (!parent->getFlippedX())
		{
			this->ghostSprite->setPositionX(this->ghostSprite->getPositionX() + this->ghostSprite->getContentSize().width);
		}
	}

	const Vec3 spriteCoords = GameUtils::getWorldCoords3D(this->ghostSprite);
	const Vec3 thisCords = GameUtils::getWorldCoords3D(this);
	const Vec3 delta = thisCords - spriteCoords;

	const float angle = this->controlTarget->getAngleRadians();
	const Vec2 position = this->controlTarget->getPosition();
	const Vec2 anchor = this->controlTarget->getPivot();

	// In order to make the game think that this AnimationPart class is the Spriter object, we need to keep certain things in sync.
	super::setRotation(angle * 180.0f / float(M_PI));
	super::setPosition(position - Vec2(delta.x, delta.y));
	super::setAnchorPoint(anchor);

	this->ghostSprite->setPosition(Vec2::ZERO);
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
