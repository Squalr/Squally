#pragma once

#include "Objects/Platformer/Doors/PuzzleDoor/PuzzleDoorBase.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;
class ConstantString;
class HackableData;
class LocalizedLabel;
class SmartAnimationSequenceNode;

class MulDoor : public PuzzleDoorBase
{
public:
	static MulDoor* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyMulDoor;

protected:
	MulDoor(cocos2d::ValueMap& initProperties);
	virtual ~MulDoor();

	void registerHackables() override;
	int onIncrement(int puzzleIndex) override;

private:
	typedef PuzzleDoorBase super;
	void showActiveHackableCrystal();
	int mulDoorTransform(int puzzleIndex);
};
