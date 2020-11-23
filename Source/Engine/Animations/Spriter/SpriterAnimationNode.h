#pragma once
#include "cocos/base/CCValue.h"

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class SpriterAnimationTimelineEventAnimation;

class SpriterAnimationNode : public SmartNode
{
public:
	static SpriterAnimationNode* create(std::string animationResource);

protected:
	SpriterAnimationNode(std::string animationResource);

	void onEnter() override;
	void update(float dt);

	void setFlippedX(bool isFlippedX);

private:
	typedef SmartNode super;

	float currentTime;

	std::map<std::string, cocos2d::Node*> bones;
	std::map<int, cocos2d::Sprite*> animationParts;
	std::map<std::string, SpriterAnimationTimelineEventAnimation*> animations;

	void loadAnimationData(std::string animationResource);
	
	cocos2d::Node* animationPartContainer;
};
