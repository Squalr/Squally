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

	void addSprite(std::string spriteResource);
	void addTrackedChild(cocos2d::Node* child);
	void setAngle(float rotation);

private:
	typedef SmartNode super;
	AnimationPart(SpriterEngine::EntityInstance* entity, std::string partName);
	virtual ~AnimationPart() = default;

	void onEnter() override;
	void update(float dt) override;

	std::vector<cocos2d::Node*> trackedChildren;
	SpriterEngine::UniversalObjectInterface* spriterAnimationPart;
	float rotation;
};
