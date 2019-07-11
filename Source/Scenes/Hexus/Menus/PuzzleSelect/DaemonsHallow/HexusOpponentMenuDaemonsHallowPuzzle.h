#pragma once

#include "Scenes/Hexus/Menus/OpponentSelect/HexusOpponentMenuBase.h"

class HexusOpponentMenuDaemonsHallowPuzzle : public HexusOpponentMenuBase
{
public:
	static HexusOpponentMenuDaemonsHallowPuzzle* getInstance();

protected:
	HexusOpponentMenuDaemonsHallowPuzzle();
	~HexusOpponentMenuDaemonsHallowPuzzle();

private:
	typedef HexusOpponentMenuBase super;
	static HexusOpponentMenuDaemonsHallowPuzzle* instance;
};
