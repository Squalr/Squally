#pragma once
#include <cstdint>
#include <functional>

#include "base/CCValue.h"

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
class SmartAnimationNode;

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
	std::string getSpriteResource(int folderId, int fileId) const;
	void playAnimation(std::string animation);
	void resetAnimation();
	void setCurrentEntity(const std::string& entityName);
	const std::string& getCurrentEntityName();
	const std::string& getCurrentAnimation();
	const std::map<std::string, SpriterAnimationBone*>& getCurrentBoneMap();
	const std::map<std::string, SpriterAnimationSprite*>& getCurrentSpriteMap();
	void setFlippedX(bool isFlippedX);
	void setFlippedY(bool isFlippedY);
	bool getFlippedX() const;
	bool getFlippedY() const;
	void setRepeating(bool isRepeating);
	bool getRepeating() const;
	void setPlaybackPaused(bool isPlaybackPaused);
	bool getPlaybackPaused() const;
	void setAnimationCompleteCallback(const std::function<void()>& callback);
	void dispatchAnimationComplete();
	void seekAnimationTimeRatio(float timeRatio);

	static const std::string DefaultAnimationEntityName;
	static const std::string DefaultAnimationName;
	
protected:
	SpriterAnimationNode(const std::string& animationResource, const std::string& entityName);
	virtual ~SpriterAnimationNode();
	bool isAnimationRoot() const override { return true; }
	cocos2d::Vec2 getCascadePosition() const override;
	cocos2d::Vec2 getCascadeScale() const override;
	float getCascadeRotation() const override;
	float getCascadeOpacityMultiplier() const override;

private:
	typedef SpriterAnimationPart super;
	friend class SmartAnimationNode;

	SpriterAnimationTimeline* timeline = nullptr;

	// Entity => Name => Bone
	std::map<std::string, std::map<std::string, SpriterAnimationBone*>> bonesByName;
	std::map<std::string, std::map<int, SpriterAnimationBone*>> bonesByHash;
	
	// Entity => Name => Sprite
	std::map<std::string, std::map<std::string, SpriterAnimationSprite*>> spritesByName;
	std::map<std::string, std::map<int, SpriterAnimationSprite*>> spritesByHash;
	std::map<uint64_t, std::string> spriteResourcesByFolderFile;
	
	// Optimization. These point to the active map for the current entity.
	std::map<std::string, SpriterAnimationBone*>* entityBonesByName = nullptr;
	std::map<int, SpriterAnimationBone*>* entityBonesByHash = nullptr;
	std::map<std::string, SpriterAnimationSprite*>* entitySpritesByName = nullptr;
	std::map<int, SpriterAnimationSprite*>* entitySpritesByHash = nullptr;

	void buildBones(const SpriterData& spriterData);
	void buildSprites(const SpriterData& spriterData, const std::string& animationResource);
	void refreshCurrentEntityAnimationState();

	std::string currentEntityName;
	std::string currentAnimation;
	std::function<void()> animationCompleteCallback = nullptr;
	std::map<std::string, std::map<std::string, SpriterAnimation>> animationDataByName;
	float previousTimelineTime = 0.0f;
	float timelineTime = 0.0f;
	bool isRepeating = true;
	bool animationCompletedThisFrame = false;
	bool playbackPaused = false;
	bool flippedX = false;
	bool flippedY = false;
};
