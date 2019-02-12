#pragma once
#include "Engine/SmartNode.h"

namespace SpriterEngine
{
	class EntityInstance;
	class UniversalObjectInterface;
}

class AnimationPart : public SmartNode
{
public:
	static AnimationPart* create(SpriterEngine::EntityInstance* entity, std::string partName);

	void detachFromTimeline();
	void replaceSprite(std::string spriteResource);
	void setRotation(float rotation) override;
	void setOffset(cocos2d::Vec2 offset);
	void setOpacity(GLubyte opacity) override;
	void setVisible(bool visible) override;

	const cocos2d::Vec2& getPosition() const override;
	cocos2d::Vec3 getPosition3D() const override;
	float getRotation() const override;

private:
	typedef SmartNode super;
	AnimationPart(SpriterEngine::EntityInstance* entity, std::string partName);
	virtual ~AnimationPart() = default;

	SpriterEngine::UniversalObjectInterface* spriterAnimationPart;
	float rotation;
};
