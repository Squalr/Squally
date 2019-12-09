#pragma once

#include "Objects/Platformer/Interactables/Doors/PuzzleDoors/PuzzleDoorBase.h"

namespace cocos2d
{
	class Sprite;
}

class StonePuzzleDoor : public PuzzleDoorBase
{
public:
	enum class DoorColor
	{
		Green,
		Yellow,
	};

protected:
	StonePuzzleDoor(cocos2d::ValueMap& properties, DoorColor doorColor);
	virtual ~StonePuzzleDoor();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	cocos2d::Vec2 getButtonOffset() override;
	HackablePreview* createDefaultPreview() override;
	virtual void runOperation(int puzzleIndex) override = 0;

	static const std::string UnlockedSaveKey;

private:
	typedef PuzzleDoorBase super;

	cocos2d::Sprite* back;
	cocos2d::Sprite* door;
	cocos2d::Sprite* front;

	static const cocos2d::Vec2 Offset;
};
