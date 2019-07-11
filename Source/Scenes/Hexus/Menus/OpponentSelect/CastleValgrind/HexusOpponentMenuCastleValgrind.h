#pragma once

#include "Scenes/Hexus/Menus/OpponentSelect/HexusOpponentMenuBase.h"

class HexusOpponentMenuCastleValgrind : public HexusOpponentMenuBase
{
public:
	static HexusOpponentMenuCastleValgrind* getInstance();

protected:
	HexusOpponentMenuCastleValgrind();
	~HexusOpponentMenuCastleValgrind();

private:
	typedef HexusOpponentMenuBase super;
	static HexusOpponentMenuCastleValgrind* instance;
};
