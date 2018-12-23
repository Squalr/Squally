#pragma once

#include "Menus/Minigames/Hexus/OpponentSelect/HexusOpponentMenuBase.h"

class HexusOpponentMenuCastle : public HexusOpponentMenuBase
{
public:
	static void registerGlobalScene();

protected:
	HexusOpponentMenuCastle();
	~HexusOpponentMenuCastle();

private:
	static HexusOpponentMenuCastle* instance;
};
