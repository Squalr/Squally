#pragma once

#include "Objects/Platformer/Interactables/Doors/PuzzleDoors/Gate/GatePuzzleDoor.h"

class MulDoorClippy;

class MulDoor : public GatePuzzleDoor
{
public:
	static MulDoor* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	MulDoor(cocos2d::ValueMap& properties);
	virtual ~MulDoor();

	void onEnter() override;
	void registerHackables() override;
	void runOperation(int puzzleIndex) override;

private:
	typedef GatePuzzleDoor super;

	void showActiveHackableCrystal();
	void mulDoorTransform(int puzzleIndex);

	MulDoorClippy* clippy;
};
