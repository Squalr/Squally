#pragma once

#include "Objects/Platformer/Interactables/Doors/PuzzleDoors/Gate/GatePuzzleDoor.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;
class ConstantString;
class HackableData;
class LocalizedLabel;
class SmartAnimationSequenceNode;

class MulDoor : public GatePuzzleDoor
{
public:
	static MulDoor* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	MulDoor(cocos2d::ValueMap& properties);
	virtual ~MulDoor();

	void registerHackables() override;
	void runOperation(int puzzleIndex) override;

private:
	typedef GatePuzzleDoor super;
	void showActiveHackableCrystal();
	void mulDoorTransform(int puzzleIndex);
};
