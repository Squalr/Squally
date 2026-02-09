#pragma once
#include "Engine/SmartNode.h"

namespace SpriterEngine
{
	class EntityInstance;
	class UniversalObjectInterface;
}

namespace cocos2d
{
	class Sprite;
}

// This class represents a part of an animation that needs to be controlled by code. Note: This class does NOT actually manage the animation part.
// This class wraps over Spriter and passes information to and from this class to the Spriter object.
// The API for this class is carefully designed, overriding cocos methods, to maintain the illusion that this is the actual animation part.
class AnimationPart : public SmartNode
{
public:
	class ControlTarget
	{
	public:
		virtual ~ControlTarget() = default;

		virtual bool isValid() const = 0;
		virtual void setTimelineCanUpdate(bool canUpdate) = 0;
		virtual std::string getSpritePath() const = 0;
		virtual void setSpritePath(const std::string& spritePath) = 0;
		virtual cocos2d::CSize getSpriteSize() const = 0;
		virtual float getAngleRadians() const = 0;
		virtual void setAngleRadians(float angleRadians) = 0;
		virtual void setOffset(const cocos2d::Vec2& offset) = 0;
		virtual void setAlphaOverride(float alphaOverride) = 0;
		virtual float getAlphaOverride() const = 0;
		virtual cocos2d::Vec2 getPosition() const = 0;
		virtual cocos2d::Vec2 getPivot() const = 0;
	};

	static AnimationPart* create(SpriterEngine::EntityInstance* entity, std::string partName);
	static AnimationPart* create(class SpriterAnimationNode* spriterAnimation, const std::string& partName);

	void removeTrackingObject(cocos2d::Node* trackedObject);
	void addTrackingObject(cocos2d::Node* trackedObject);
	void replaceWithObject(cocos2d::Node* replacement, float disappearDuration = 2.0f, float fadeInDuration = 0.5f);
	void reattachToTimeline();
	void detachFromTimeline();
	std::string getSpriteResource();
	void replaceSprite(std::string spriteResource);
	void restoreSprite();
	void setRotation(float rotation) override;
	float getRotationSpriter();
	void setRotationSpriter(float rotation);
	void setOffset(cocos2d::Vec2 offset);
	void restoreOffset();
	void setOpacity(GLubyte opacity) override;
	void setVisible(bool visible) override;
	void updateTrackedAttributes();

	GLubyte getOpacity() const override;
	cocos2d::CSize getSpriteSize();

private:
	typedef SmartNode super;
	AnimationPart(ControlTarget* controlTarget);
	virtual ~AnimationPart();

	void onEnter() override;
	void update(float dt) override;
	void visit(cocos2d::Renderer *renderer, const cocos2d::Mat4& parentTransform, uint32_t parentFlags) override;
	void onDeveloperModeEnable(int debugLevel) override;
	void onDeveloperModeDisable() override;

	std::string originalPath;
	std::string ghostSpritePath;
	std::vector<cocos2d::Node*> trackedObjects;
	cocos2d::Sprite* ghostSprite = nullptr;
	ControlTarget* controlTarget = nullptr;
	float rotation = 0.0f;
	std::string lastKnownAnim;
};
