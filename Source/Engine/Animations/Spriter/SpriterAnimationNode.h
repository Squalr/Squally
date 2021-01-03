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

	SpriterAnimationPart* getPartByName(const std::string& name);
	SpriterAnimationBone* getBoneByName(const std::string& name);
	SpriterAnimationSprite* getSpriteByName(const std::string& name);
	SpriterAnimationPart* getPartByHash(int id);
	SpriterAnimationBone* getBoneByHash(int id);
	SpriterAnimationSprite* getSpriteByHash(int id);
	void playAnimation(std::string animation);
	void resetAnimation();
	void setCurrentEntity(const std::string& entityName);
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
	std::map<std::string, std::map<std::string, SpriterAnimationBone*>> bonesByName;
	std::map<std::string, std::map<int, SpriterAnimationBone*>> bonesByHash;
	
	// Entity => Name => Sprite
	std::map<std::string, std::map<std::string, SpriterAnimationSprite*>> spritesByName;
	std::map<std::string, std::map<int, SpriterAnimationSprite*>> spritesByHash;
	
	// Optimization. These point to the active map for the current entity.
	std::map<std::string, SpriterAnimationBone*>* entityBonesByName;
	std::map<int, SpriterAnimationBone*>* entityBonesByHash;
	std::map<std::string, SpriterAnimationSprite*>* entitySpritesByName;
	std::map<int, SpriterAnimationSprite*>* entitySpritesByHash;

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
