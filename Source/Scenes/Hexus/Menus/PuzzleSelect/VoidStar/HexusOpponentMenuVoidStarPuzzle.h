#pragma once

#include "Scenes/Hexus/Menus/OpponentSelect/HexusOpponentMenuBase.h"

class HexusOpponentMenuVoidStarPuzzle : public HexusOpponentMenuBase
{
public:
	static HexusOpponentMenuVoidStarPuzzle* getInstance();

protected:
	HexusOpponentMenuVoidStarPuzzle();
	~HexusOpponentMenuVoidStarPuzzle();

private:
	typedef HexusOpponentMenuBase super;
	static HexusOpponentMenuVoidStarPuzzle* instance;
};
