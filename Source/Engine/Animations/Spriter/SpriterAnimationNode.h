#pragma once
#include "cocos/base/CCValue.h"

#include "Engine/SmartNode.h"

#include "Engine/Animations/Spriter/SpriterStructs.h"

namespace cocos2d
{
	class Sprite;
}

class SpriterAnimationPart;
class SpriterAnimationTimeline;

class SpriterAnimationNode : public SmartNode
{
public:
	static SpriterAnimationNode* create(const std::string& animationResource);

	// For use by animation timelines
	void advanceTimelineTime(float dt, float timelineMax);
	float getPreviousTimelineTime();
	float getTimelineTime();

	SpriterAnimationPart* getPartById(const std::string& name);
	void playAnimation(std::string animation);
	void resetAnimation();
	const std::string& getCurrentEntityName();
	const std::string& getCurrentAnimation();

protected:
	SpriterAnimationNode(const std::string& animationResource);
	virtual ~SpriterAnimationNode();

	void setFlippedX(bool isFlippedX);

private:
	typedef SmartNode super;

	SpriterAnimationTimeline* timeline;

	// Entity => Name => Bone
	std::map<std::string, std::map<std::string, SpriterAnimationPart*>> bones;
	std::map<int, SpriterAnimationPart*> boneIdMap;
	
	// Entity => Name => Sprite
	std::map<std::string, std::map<std::string, SpriterAnimationPart*>> sprites;
	std::map<int, SpriterAnimationPart*> spriteIdMap;

	void buildBones(const SpriterData& spriterData);
	void buildSprites(const SpriterData& spriterData, const std::string& animationResource);
	
	cocos2d::Node* animationPartContainer;

	std::string currentEntityName;
	std::string currentAnimation;
	float previousTimelineTime;
	float timelineTime;
	bool isRepeating;
	
	static const std::string DefaultAnimationEntityName;
	static const std::string DefaultAnimationName;
};
