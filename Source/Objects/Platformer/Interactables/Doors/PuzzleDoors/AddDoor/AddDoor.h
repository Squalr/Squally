#pragma once

#include "Objects/Platformer/Interactables/Doors/PuzzleDoors/StoneDoor/StonePuzzleDoor.h"

class AddDoorClippy;

class AddDoor : public StonePuzzleDoor
{
public:
	static AddDoor* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	AddDoor(cocos2d::ValueMap& properties);
	virtual ~AddDoor();

	void onEnter() override;
	void registerHackables() override;
	void runOperation(int puzzleIndex) override;

private:
	typedef StonePuzzleDoor super;

	void showActiveHackableCrystal();
	void AddDoorTransform(int puzzleIndex);

	AddDoorClippy* clippy;
};
