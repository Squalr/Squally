#pragma once

#include "Scenes/Hexus/Menus/OpponentSelect/HexusOpponentMenuBase.h"

class HexusOpponentMenuDaemonsHallow : public HexusOpponentMenuBase
{
public:
	static HexusOpponentMenuDaemonsHallow* getInstance();

protected:
	HexusOpponentMenuDaemonsHallow();
	~HexusOpponentMenuDaemonsHallow();

private:
	typedef HexusOpponentMenuBase super;
	static HexusOpponentMenuDaemonsHallow* instance;
};
