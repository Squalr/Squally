#include "SpriterAnimationPart.h"

#include <algorithm>
#include <cmath>

#include "Engine/Utils/GameUtils.h"

using namespace cocos2d;

namespace
{
	AffineTransform buildAnimationTransform(const Vec2& position, const Vec2& scale, float rotation)
	{
		const float rotationRadians = -rotation * float(M_PI) / 180.0f;
		const float rotationCos = std::cos(rotationRadians);
		const float rotationSin = std::sin(rotationRadians);

		return AffineTransformMake(
			rotationCos * scale.x,
			rotationSin * scale.x,
			-rotationSin * scale.y,
			rotationCos * scale.y,
			position.x,
			position.y
		);
	}
}

SpriterAnimationPart::SpriterAnimationPart()
{
	this->resolvedAnimationTransform = AffineTransformMakeIdentity();
}

SpriterAnimationPart::~SpriterAnimationPart()
{
}

void SpriterAnimationPart::addAnimationPartChild(SpriterAnimationPart* part)
{
    part->parentPart = this;
    this->childAnimationParts.push_back(part);

	GameUtils::changeParent(part, this->getAnimationRootPart(), false);

	if (part->canTimelineUpdate())
	{
		part->refreshAnimationState();
	}
}

void SpriterAnimationPart::clearAnimationPartChildren()
{
    this->childAnimationParts.clear();
}

void SpriterAnimationPart::applyAnimationState(const Vec2& position, const Vec2& anchor, const Vec2& scale, float rotation, GLubyte opacity)
{
	this->timelinePosition = position;
	this->timelineAnchor = anchor;
	this->timelineScale = scale;
	this->timelineRotation = rotation;
	this->timelineOpacity = opacity;

	if (this->timelineUpdatesEnabled)
	{
		this->refreshAnimationState();
	}
}

void SpriterAnimationPart::setTimelineCanUpdate(bool canTimelineUpdate)
{
	this->timelineUpdatesEnabled = canTimelineUpdate;

	if (canTimelineUpdate)
	{
		this->refreshAnimationState();
	}
}

bool SpriterAnimationPart::canTimelineUpdate() const
{
	return this->timelineUpdatesEnabled;
}

bool SpriterAnimationPart::isAnimationRoot() const
{
	return false;
}

void SpriterAnimationPart::setCompatibilityLayoutEnabled(bool enabled)
{
	this->compatibilityLayoutEnabled = enabled;
	this->applyResolvedAnimationState(
		this->resolvedAnimationPosition,
		this->timelineAnchor,
		this->resolvedAnimationScale,
		this->resolvedAnimationRotation,
		this->resolvedAnimationOpacity
	);
}

bool SpriterAnimationPart::isCompatibilityLayoutEnabled() const
{
	return this->compatibilityLayoutEnabled;
}

bool SpriterAnimationPart::usesCompatibilityLayout() const
{
	return false;
}

void SpriterAnimationPart::setAnimationOffset(const Vec2& offset)
{
	this->animationOffset = offset;

	if (this->timelineUpdatesEnabled)
	{
		this->refreshAnimationState();
	}
	else
	{
		this->applyAnimationOffset(this->animationOffset);
	}
}

void SpriterAnimationPart::clearAnimationOffset()
{
	this->setAnimationOffset(Vec2::ZERO);
}

Vec2 SpriterAnimationPart::getAnimationOffset() const
{
	return this->animationOffset;
}

void SpriterAnimationPart::setAlphaOverride(float alphaOverride)
{
	this->alphaOverride = alphaOverride;

	if (this->timelineUpdatesEnabled)
	{
		this->refreshAnimationState();
	}
	else
	{
		super::setOpacity(alphaOverride >= 0.0f ? GLubyte(alphaOverride * 255.0f) : this->timelineOpacity);
	}
}

float SpriterAnimationPart::getAlphaOverride() const
{
	return this->alphaOverride;
}

Vec2 SpriterAnimationPart::getAnimationAnchorPoint() const
{
	return this->timelineAnchor;
}

void SpriterAnimationPart::setSpriteResource(const std::string& spriteResource)
{
}

void SpriterAnimationPart::restoreSpriteResource()
{
}

std::string SpriterAnimationPart::getSpriteResource() const
{
	return "";
}

CSize SpriterAnimationPart::getSpriteSize() const
{
	return CSize::ZERO;
}

cocos2d::AffineTransform SpriterAnimationPart::getResolvedAnimationTransform() const
{
	return this->resolvedAnimationTransform;
}

cocos2d::Vec2 SpriterAnimationPart::getResolvedAnimationPosition() const
{
	return this->resolvedAnimationPosition;
}

cocos2d::Vec2 SpriterAnimationPart::getResolvedAnimationScale() const
{
	return this->resolvedAnimationScale;
}

float SpriterAnimationPart::getResolvedAnimationRotation() const
{
	return this->resolvedAnimationRotation;
}

GLubyte SpriterAnimationPart::getResolvedAnimationOpacity() const
{
	return this->resolvedAnimationOpacity;
}

void SpriterAnimationPart::applyResolvedAnimationState(const Vec2& position, const Vec2& anchor, const Vec2& scale, float rotation, GLubyte opacity)
{
	this->resolvedAnimationPosition = position;
	this->resolvedAnimationScale = scale;
	this->resolvedAnimationRotation = rotation;
	this->resolvedAnimationOpacity = opacity;
	this->applyAnchorPoint(anchor);
	super::setPosition(position);
	super::setScale(scale);
	super::setRotation(rotation);
	super::setOpacity(opacity);
	this->applyAnimationOffset(this->animationOffset);
}

void SpriterAnimationPart::applyAnchorPoint(const Vec2& anchorPoint)
{
}

void SpriterAnimationPart::applyAnimationOffset(const Vec2& offset)
{
}

Vec2 SpriterAnimationPart::getCascadePosition() const
{
	return this->resolvedAnimationPosition;
}

Vec2 SpriterAnimationPart::getCascadeScale() const
{
	return this->resolvedAnimationScale;
}

float SpriterAnimationPart::getCascadeRotation() const
{
	return this->resolvedAnimationRotation;
}

float SpriterAnimationPart::getCascadeOpacityMultiplier() const
{
	return float(this->resolvedAnimationOpacity) / 255.0f;
}

SpriterAnimationPart* SpriterAnimationPart::getAnimationRootPart()
{
	SpriterAnimationPart* rootPart = this;

	while (rootPart->parentPart != nullptr)
	{
		rootPart = rootPart->parentPart;
	}

	return rootPart;
}

void SpriterAnimationPart::refreshAnimationState()
{
	const float localOpacity = this->alphaOverride >= 0.0f
		? this->alphaOverride * 255.0f
		: this->timelineOpacity;
	const Vec2 localPosition = this->timelinePosition;
	Vec2 resolvedPosition = localPosition;
	Vec2 resolvedScale = this->timelineScale;
	float resolvedRotation = this->timelineRotation;
	float resolvedOpacity = localOpacity;

	if (this->parentPart != nullptr)
	{
		const Vec2 parentPosition = this->parentPart->getCascadePosition();
		const Vec2 parentScale = this->parentPart->getCascadeScale();
		const float parentRotation = this->parentPart->getCascadeRotation();
		const float parentOpacity = this->parentPart->getCascadeOpacityMultiplier();
		const float reflectionSign = parentScale.x * parentScale.y < 0.0f ? -1.0f : 1.0f;
		const float parentRotationRadians = -parentRotation * float(M_PI) / 180.0f;
		const float parentRotationCos = std::cos(parentRotationRadians);
		const float parentRotationSin = std::sin(parentRotationRadians);
		const Vec2 scaledLocalPosition(localPosition.x * parentScale.x, localPosition.y * parentScale.y);

		resolvedPosition = parentPosition + Vec2(
			scaledLocalPosition.x * parentRotationCos - scaledLocalPosition.y * parentRotationSin,
			scaledLocalPosition.x * parentRotationSin + scaledLocalPosition.y * parentRotationCos
		);
		resolvedScale = Vec2(this->timelineScale.x * parentScale.x, this->timelineScale.y * parentScale.y);
		resolvedRotation = parentRotation + this->timelineRotation * reflectionSign;
		resolvedOpacity *= parentOpacity;
	}

	this->applyResolvedAnimationState(
		resolvedPosition,
		this->timelineAnchor,
		resolvedScale,
		resolvedRotation,
		GLubyte(std::round(std::max(0.0f, std::min(255.0f, resolvedOpacity))))
	);
	this->resolvedAnimationTransform = buildAnimationTransform(resolvedPosition, resolvedScale, resolvedRotation);

	for (SpriterAnimationPart* childAnimationPart : this->childAnimationParts)
	{
		if (childAnimationPart != nullptr && childAnimationPart->canTimelineUpdate())
		{
			childAnimationPart->refreshAnimationState();
		}
	}
}
