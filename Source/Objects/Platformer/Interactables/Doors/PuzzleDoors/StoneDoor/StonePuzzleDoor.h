#pragma once

#include "Objects/Platformer/Interactables/Doors/PuzzleDoors/PuzzleDoorBase.h"

namespace cocos2d
{
	class Sprite;
}

class StonePuzzleDoor : public PuzzleDoorBase
{
public:

protected:
	StonePuzzleDoor(cocos2d::ValueMap& properties);
	virtual ~StonePuzzleDoor();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	cocos2d::Vec2 getButtonOffset() override;
	cocos2d::Vec2 getRainOffset() override;
	HackablePreview* createDefaultPreview() override;
	virtual void runOperation(int puzzleIndex) override = 0;

private:
	typedef PuzzleDoorBase super;

	cocos2d::Sprite* back;
	cocos2d::Sprite* door;
	cocos2d::Sprite* front;

	static const cocos2d::Vec2 Offset;
	static const std::string PropertyColor;
};
