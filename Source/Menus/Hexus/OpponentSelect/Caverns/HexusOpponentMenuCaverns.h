#pragma once

#include "Menus/Hexus/OpponentSelect/HexusOpponentMenuBase.h"

class HexusOpponentMenuCaverns : public HexusOpponentMenuBase
{
public:
	static void registerGlobalScene();

protected:
	HexusOpponentMenuCaverns();
	~HexusOpponentMenuCaverns();

private:
	typedef HexusOpponentMenuBase super;
	static HexusOpponentMenuCaverns* instance;
};
