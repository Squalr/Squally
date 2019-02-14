#pragma once

#include "Scenes/Hexus/Menus/OpponentSelect/HexusOpponentMenuBase.h"

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
