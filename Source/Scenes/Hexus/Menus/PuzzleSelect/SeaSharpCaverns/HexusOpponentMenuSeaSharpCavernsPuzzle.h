#pragma once

#include "Scenes/Hexus/Menus/OpponentSelect/HexusOpponentMenuBase.h"

class HexusOpponentMenuSeaSharpCavernsPuzzle : public HexusOpponentMenuBase
{
public:
	static HexusOpponentMenuSeaSharpCavernsPuzzle* getInstance();

protected:
	HexusOpponentMenuSeaSharpCavernsPuzzle();
	~HexusOpponentMenuSeaSharpCavernsPuzzle();

private:
	typedef HexusOpponentMenuBase super;
	static HexusOpponentMenuSeaSharpCavernsPuzzle* instance;
};
