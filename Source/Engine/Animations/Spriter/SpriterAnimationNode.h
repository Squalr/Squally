#pragma once
#include "cocos/base/CCValue.h"

#include "Engine/Animations/Spriter/SpriterAnimationPart.h"

#include "Engine/Animations/Spriter/SpriterStructs.h"

namespace cocos2d
{
	class Sprite;
}

class SpriterAnimationBone;
class SpriterAnimationPart;
class SpriterAnimationSprite;
class SpriterAnimationTimeline;

class SpriterAnimationNode : public SpriterAnimationPart
{
public:
	static SpriterAnimationNode* create(const std::string& animationResource);

	// For use by animation timelines
	void advanceTimelineTime(float dt, float timelineMax);
	float getPreviousTimelineTime();
	float getTimelineTime();

	SpriterAnimationPart* getPartById(const std::string& name);
	SpriterAnimationBone* getBoneById(const std::string& name);
	SpriterAnimationSprite* getSpriteById(const std::string& name);
	void playAnimation(std::string animation);
	void resetAnimation();
	const std::string& getCurrentEntityName();
	const std::string& getCurrentAnimation();
	const std::map<std::string, SpriterAnimationBone*>& getCurrentBoneMap();
	const std::map<std::string, SpriterAnimationSprite*>& getCurrentSpriteMap();
	void setFlippedX(bool isFlippedX);

protected:
	SpriterAnimationNode(const std::string& animationResource);
	virtual ~SpriterAnimationNode();

private:
	typedef SpriterAnimationPart super;

	SpriterAnimationTimeline* timeline;

	// Entity => Name => Bone
	std::map<std::string, std::map<std::string, SpriterAnimationBone*>> bones;
	std::map<int, SpriterAnimationBone*> boneIdMap;
	
	// Entity => Name => Sprite
	std::map<std::string, std::map<std::string, SpriterAnimationSprite*>> sprites;
	std::map<int, SpriterAnimationSprite*> spriteIdMap;

	void buildBones(const SpriterData& spriterData);
	void buildSprites(const SpriterData& spriterData, const std::string& animationResource);

	std::string currentEntityName;
	std::string currentAnimation;
	float previousTimelineTime;
	float timelineTime;
	bool isRepeating;
	
	static const std::string DefaultAnimationEntityName;
	static const std::string DefaultAnimationName;
};
