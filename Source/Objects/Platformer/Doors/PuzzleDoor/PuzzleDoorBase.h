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
	virtual int onIncrement(int puzzleIndex) = 0;

private:
	typedef HackableObject super;

	cocos2d::Sprite* back;
	cocos2d::Sprite* door;
	cocos2d::Sprite* front;
	ConstantString* indexString;
	ConstantString* truthString;
	ConstantString* hackableString;
	LocalizedLabel* indexLabel;
	LocalizedLabel* truthLabel;
	LocalizedLabel* hackableLabel;

	bool isUnlocked;
	int puzzleIndex;
};
