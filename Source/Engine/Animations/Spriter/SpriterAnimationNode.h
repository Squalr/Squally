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
	static SpriterAnimationNode* create(const std::string& animationResource, const std::string& entityName);

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

	static const std::string DefaultAnimationEntityName;
	static const std::string DefaultAnimationName;
	
protected:
	SpriterAnimationNode(const std::string& animationResource, const std::string& entityName);
	virtual ~SpriterAnimationNode();

private:
	typedef SpriterAnimationPart super;

	SpriterAnimationTimeline* timeline = nullptr;

	// Entity => Name => Bone
	std::map<std::string, std::map<std::string, SpriterAnimationBone*>> bonesByName;
	std::map<std::string, std::map<int, SpriterAnimationBone*>> bonesByHash;
	
	// Entity => Name => Sprite
	std::map<std::string, std::map<std::string, SpriterAnimationSprite*>> spritesByName;
	std::map<std::string, std::map<int, SpriterAnimationSprite*>> spritesByHash;
	
	// Optimization. These point to the active map for the current entity.
	std::map<std::string, SpriterAnimationBone*>* entityBonesByName = nullptr;
	std::map<int, SpriterAnimationBone*>* entityBonesByHash = nullptr;
	std::map<std::string, SpriterAnimationSprite*>* entitySpritesByName = nullptr;
	std::map<int, SpriterAnimationSprite*>* entitySpritesByHash = nullptr;

	void buildBones(const SpriterData& spriterData);
	void buildSprites(const SpriterData& spriterData, const std::string& animationResource);

	std::string currentEntityName;
	std::string currentAnimation;
	float previousTimelineTime = 0.0f;
	float timelineTime = 0.0f;
	bool isRepeating = true;
};
