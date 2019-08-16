#pragma once

#include "Objects/Platformer/Doors/Portal.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableNode;
class CollisionObject;
class ConstantString;
class InteractMenu;
class LocalizedLabel;
class SmartAnimationSequenceNode;
class SmartClippingNode;
class Sound;

class PuzzleDoorBase : public Portal
{
public:
	void lock(bool animate = true) override;
	void unlock(bool animate = true) override;

protected:
	PuzzleDoorBase(cocos2d::ValueMap& properties);
	~PuzzleDoorBase();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void onObjectStateLoaded() override;
	cocos2d::Vec2 getButtonOffset() override;
	HackablePreview* createDefaultPreview() override;
	virtual void runOperation(int puzzleIndex) = 0;
	void setRealValue(int value);
	void setHackValue(int value);

	static const std::string UnlockedSaveKey;

private:
	typedef Portal super;

	cocos2d::Sprite* back;
	cocos2d::Sprite* lightLeft;
	cocos2d::Sprite* lightRight;
	cocos2d::Sprite* door;
	SmartClippingNode* doorClip;
	cocos2d::Sprite* front;
	std::vector<cocos2d::Sprite*> runes;
	std::vector<cocos2d::Sprite*> runesPassed;
	std::vector<cocos2d::Sprite*> runesFailed;
	ConstantString* indexString;
	ConstantString* truthString;
	ConstantString* hackableString;
	LocalizedLabel* indexLabel;
	LocalizedLabel* truthLabel;
	LocalizedLabel* hackableLabel;
	Sound* doorOpenSound;

	bool firstRun;
	bool isUnlocked;
	int passedCount;
	int puzzleIndex;
	int realValue;
	int hackValue;

	static const int RuneCount;
	static const cocos2d::Color4B PassColor;
	static const cocos2d::Color4B FailColor;
	static const cocos2d::Vec2 Offset;
	static const cocos2d::Vec2 DoorOffset;
	static const cocos2d::Vec2 DoorOpenOffset;
};
