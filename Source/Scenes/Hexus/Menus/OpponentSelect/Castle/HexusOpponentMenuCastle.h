#pragma once

#include "Scenes/Hexus/Menus/OpponentSelect/HexusOpponentMenuBase.h"

class HexusOpponentMenuCastle : public HexusOpponentMenuBase
{
public:
	static void registerGlobalScene();

protected:
	HexusOpponentMenuCastle();
	~HexusOpponentMenuCastle();

private:
	typedef HexusOpponentMenuBase super;
	static HexusOpponentMenuCastle* instance;
};
