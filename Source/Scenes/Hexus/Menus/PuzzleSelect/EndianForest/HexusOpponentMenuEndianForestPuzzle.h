#pragma once

#include "Scenes/Hexus/Menus/OpponentSelect/HexusOpponentMenuBase.h"

class HexusOpponentMenuEndianForestPuzzle : public HexusOpponentMenuBase
{
public:
	static HexusOpponentMenuEndianForestPuzzle* getInstance();

protected:
	HexusOpponentMenuEndianForestPuzzle();
	~HexusOpponentMenuEndianForestPuzzle();

private:
	typedef HexusOpponentMenuBase super;
	static HexusOpponentMenuEndianForestPuzzle* instance;
};
