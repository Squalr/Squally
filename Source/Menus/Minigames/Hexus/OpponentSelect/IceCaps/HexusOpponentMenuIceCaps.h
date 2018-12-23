#pragma once

#include "Menus/Minigames/Hexus/OpponentSelect/HexusOpponentMenuBase.h"

class HexusOpponentMenuIceCaps : public HexusOpponentMenuBase
{
public:
	static void registerGlobalScene();

protected:
	HexusOpponentMenuIceCaps();
	~HexusOpponentMenuIceCaps();

private:
	static HexusOpponentMenuIceCaps* instance;
};
