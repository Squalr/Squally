#pragma once

#include "Scenes/Hexus/Menus/OpponentSelect/HexusOpponentMenuBase.h"

class HexusOpponentMenuMech : public HexusOpponentMenuBase
{
public:
	static void registerGlobalScene();

protected:
	HexusOpponentMenuMech();
	~HexusOpponentMenuMech();

private:
	typedef HexusOpponentMenuBase super;
	static HexusOpponentMenuMech* instance;
};
