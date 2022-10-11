#pragma once

#include "Objects/Platformer/Interactables/Doors/Portal.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;
class ConstantString;
class InteractMenu;
class LocalizedLabel;
class SmartAnimationSequenceNode;
class SmartClippingNode;
class WorldSound;

class PuzzleDoorBase : public Portal
{
public:
	void lock(bool animate = true) override;
	void unlock(bool animate = true) override;

	bool getIsUnlocked();

	static const std::string PropertyUnlockedByDefault;

protected:
	PuzzleDoorBase(cocos2d::ValueMap& properties,
		cocos2d::CSize doorClipSize,
		cocos2d::Vec2 doorClipOffset,
		cocos2d::Vec2 portalOffset,
		cocos2d::Vec2 indexPosition,
		cocos2d::Vec2 hackLabelPosition,
		cocos2d::Vec2 truthLabelPosition,
		cocos2d::Vec2 runeBasePosition,
		float runeSpacing,
		float doorOpenDelta);
	virtual ~PuzzleDoorBase();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	virtual void runOperation(int puzzleIndex) = 0;
	void setRealValue(int value);
	void setHackValue(int value);
	
	cocos2d::Node* backNode = nullptr;
	cocos2d::Node* doorNode = nullptr;
	SmartClippingNode* doorClip = nullptr;
	cocos2d::Node* frontNode = nullptr;
	WorldSound* doorOpenSound = nullptr;
	WorldSound* sliderSound = nullptr;
	WorldSound* sliderResetSound = nullptr;
	WorldSound* electricitySound = nullptr;

	static const std::string UnlockedSaveKey;

private:
	typedef Portal super;

	cocos2d::Sprite* barLeft = nullptr;
	cocos2d::Sprite* barRight = nullptr;
	cocos2d::Sprite* lightLeft = nullptr;
	cocos2d::Sprite* lightRight = nullptr;
	cocos2d::Sprite* marker = nullptr;
	std::vector<cocos2d::Sprite*> runes;
	std::vector<cocos2d::Sprite*> runesPassed;
	std::vector<cocos2d::Sprite*> runesFailed;
	ConstantString* indexString = nullptr;
	ConstantString* truthString = nullptr;
	ConstantString* hackableString = nullptr;
	LocalizedLabel* indexLabel = nullptr;
	LocalizedLabel* truthLabel = nullptr;
	LocalizedLabel* hackableLabel = nullptr;

	// Positioning parameters
	cocos2d::CSize doorClipSize;
	cocos2d::Vec2 doorClipOffset;
	cocos2d::Vec2 portalOffset;
	cocos2d::Vec2 indexPosition;
	cocos2d::Vec2 hackLabelPosition;
	cocos2d::Vec2 truthLabelPosition;
	cocos2d::Vec2 runeBasePosition;
	float runeSpacing = 0.0f;
	float doorOpenDelta = 0.0f;

	enum RuneState
	{
		Unset,
		Passed,
		Failed
	};

	bool unlockedByDefault = false;
	bool firstRun = false;
	bool isUnlocked = false;
	RuneState runeStates[4];
	int puzzleIndex = 0;
	int realValue = 0;
	int hackValue = 0;

	static const int RuneCount;
	static const cocos2d::Color4B PassColor;
	static const cocos2d::Color4B FailColor;
};
