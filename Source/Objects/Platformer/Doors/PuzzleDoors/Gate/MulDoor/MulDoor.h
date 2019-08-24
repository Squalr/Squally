#pragma once

#include "Objects/Platformer/Doors/PuzzleDoors/GreenStoneDoor/GreenStonePuzzleDoor.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;
class ConstantString;
class HackableData;
class LocalizedLabel;
class SmartAnimationSequenceNode;

class MulDoor : public GreenStonePuzzleDoor
{
public:
	static MulDoor* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyMulDoor;

protected:
	MulDoor(cocos2d::ValueMap& properties);
	~MulDoor();

	void registerHackables() override;
	void runOperation(int puzzleIndex) override;

private:
	typedef GreenStonePuzzleDoor super;
	void showActiveHackableCrystal();
	void mulDoorTransform(int puzzleIndex);
};
