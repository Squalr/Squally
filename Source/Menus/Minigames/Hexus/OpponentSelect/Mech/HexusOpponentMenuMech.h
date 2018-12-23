#pragma once

#include "Menus/Minigames/Hexus/OpponentSelect/HexusOpponentMenuBase.h"

class HexusOpponentMenuMech : public HexusOpponentMenuBase
{
public:
	static void registerGlobalScene();

protected:
	HexusOpponentMenuMech();
	~HexusOpponentMenuMech();

private:
	static HexusOpponentMenuMech* instance;
};
