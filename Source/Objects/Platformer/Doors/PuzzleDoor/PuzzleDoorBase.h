#pragma once

#include "Engine/Hackables/HackableObject.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;
class ConstantString;
class HackableData;
class LocalizedLabel;
class SmartAnimationSequenceNode;
class SmartClippingNode;
class Sound;

class PuzzleDoorBase : public HackableObject
{
public:

protected:
	PuzzleDoorBase(cocos2d::ValueMap& initProperties);
	virtual ~PuzzleDoorBase();

	void onEnter() override;
	void initializePositions() override;
	cocos2d::Vec2 getButtonOffset() override;
	HackablePreview* createDefaultPreview() override;
	virtual void runOperation(int puzzleIndex) = 0;
	void setRealValue(int value);
	void setHackValue(int value);

private:
	typedef HackableObject super;

	void unlock(bool animate = true);

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
};
