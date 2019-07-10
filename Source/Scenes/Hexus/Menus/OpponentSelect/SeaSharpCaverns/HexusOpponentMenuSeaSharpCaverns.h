#pragma once

#include "Scenes/Hexus/Menus/OpponentSelect/HexusOpponentMenuBase.h"

class HexusOpponentMenuSeaSharpCaverns : public HexusOpponentMenuBase
{
public:
	static HexusOpponentMenuSeaSharpCaverns* getInstance();

protected:
	HexusOpponentMenuSeaSharpCaverns();
	~HexusOpponentMenuSeaSharpCaverns();

private:
	typedef HexusOpponentMenuBase super;
	static HexusOpponentMenuSeaSharpCaverns* instance;
};
