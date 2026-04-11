#pragma once
#include <string>

#include "base/CCValue.h"
#include "base/ccTypes.h"
#include "math/CCGeometry.h"
#include "math/Vec2.h"

#include "Engine/SmartNode.h"

class SpriterAnimationPart : public SmartNode
{
public:
	void addAnimationPartChild(SpriterAnimationPart* part);
	void clearAnimationPartChildren();
	void applyAnimationState(const cocos2d::Vec2& position, const cocos2d::Vec2& anchor, const cocos2d::Vec2& scale, float rotation, GLubyte opacity);
	void setTimelineCanUpdate(bool canTimelineUpdate);
	bool canTimelineUpdate() const;
	virtual bool isAnimationRoot() const;
	virtual void setCompatibilityLayoutEnabled(bool enabled);
	bool isCompatibilityLayoutEnabled() const;
	virtual bool usesCompatibilityLayout() const;
	void setAnimationOffset(const cocos2d::Vec2& offset);
	void clearAnimationOffset();
	cocos2d::Vec2 getAnimationOffset() const;
	void setAlphaOverride(float alphaOverride);
	float getAlphaOverride() const;
	cocos2d::Vec2 getAnimationAnchorPoint() const;
	virtual void setSpriteResource(const std::string& spriteResource);
	virtual void restoreSpriteResource();
	virtual std::string getSpriteResource() const;
	virtual cocos2d::CSize getSpriteSize() const;
	cocos2d::AffineTransform getResolvedAnimationTransform() const;
	cocos2d::Vec2 getResolvedAnimationPosition() const;
	cocos2d::Vec2 getResolvedAnimationScale() const;
	float getResolvedAnimationRotation() const;
	GLubyte getResolvedAnimationOpacity() const;

protected:
	friend class SpriterAnimationTimeline;
	friend class SpriterAnimationTimelineEventMainline;
	friend class SpriterAnimationNode;

	SpriterAnimationPart();
	virtual ~SpriterAnimationPart();

	virtual void applyResolvedAnimationState(const cocos2d::Vec2& position, const cocos2d::Vec2& anchor, const cocos2d::Vec2& scale, float rotation, GLubyte opacity);
	virtual void applyAnchorPoint(const cocos2d::Vec2& anchorPoint);
	virtual void applyAnimationOffset(const cocos2d::Vec2& offset);
	virtual cocos2d::Vec2 getCascadePosition() const;
	virtual cocos2d::Vec2 getCascadeScale() const;
	virtual float getCascadeRotation() const;
	virtual float getCascadeOpacityMultiplier() const;
	void refreshAnimationState();
	SpriterAnimationPart* getAnimationRootPart();
	
	SpriterAnimationPart* parentPart = nullptr;
	std::vector<SpriterAnimationPart*> childAnimationParts;
	cocos2d::Vec2 timelinePosition = cocos2d::Vec2::ZERO;
	cocos2d::Vec2 timelineAnchor = cocos2d::Vec2::ZERO;
	cocos2d::Vec2 timelineScale = cocos2d::Vec2::ONE;
	cocos2d::AffineTransform resolvedAnimationTransform;
	cocos2d::Vec2 resolvedAnimationPosition = cocos2d::Vec2::ZERO;
	cocos2d::Vec2 resolvedAnimationScale = cocos2d::Vec2::ONE;
	cocos2d::Vec2 animationOffset = cocos2d::Vec2::ZERO;
	float timelineRotation = 0.0f;
	float resolvedAnimationRotation = 0.0f;
	float alphaOverride = -1.0f;
	GLubyte timelineOpacity = 255;
	GLubyte resolvedAnimationOpacity = 255;
	bool timelineUpdatesEnabled = true;
	bool compatibilityLayoutEnabled = true;
	
private:
	typedef SmartNode super;
};
