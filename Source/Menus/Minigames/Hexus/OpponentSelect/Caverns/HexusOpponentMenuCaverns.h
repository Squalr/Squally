#pragma once

#include "Menus/Minigames/Hexus/OpponentSelect/HexusOpponentMenuBase.h"

class HexusOpponentMenuCaverns : public HexusOpponentMenuBase
{
public:
	static void registerGlobalScene();

protected:
	HexusOpponentMenuCaverns();
	~HexusOpponentMenuCaverns();

private:
	static HexusOpponentMenuCaverns* instance;
};
