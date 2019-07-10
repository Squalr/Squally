#pragma once

#include "Scenes/Hexus/Menus/OpponentSelect/HexusOpponentMenuBase.h"

class HexusOpponentMenuCastleValgrindPuzzle : public HexusOpponentMenuBase
{
public:
	static HexusOpponentMenuCastleValgrindPuzzle* getInstance();

protected:
	HexusOpponentMenuCastleValgrindPuzzle();
	~HexusOpponentMenuCastleValgrindPuzzle();

private:
	typedef HexusOpponentMenuBase super;
	static HexusOpponentMenuCastleValgrindPuzzle* instance;
};
