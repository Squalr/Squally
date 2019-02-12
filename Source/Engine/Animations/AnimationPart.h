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
	void setAngle(float rotation);
	void setOffset(cocos2d::Vec2 offset);

private:
	typedef SmartNode super;
	AnimationPart(SpriterEngine::EntityInstance* entity, std::string partName);
	virtual ~AnimationPart() = default;

	SpriterEngine::UniversalObjectInterface* spriterAnimationPart;
	float rotation;
};
