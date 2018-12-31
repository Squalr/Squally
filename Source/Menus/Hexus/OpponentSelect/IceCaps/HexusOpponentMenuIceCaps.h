#pragma once

#include "Menus/Hexus/OpponentSelect/HexusOpponentMenuBase.h"

class HexusOpponentMenuIceCaps : public HexusOpponentMenuBase
{
public:
	static void registerGlobalScene();

protected:
	HexusOpponentMenuIceCaps();
	~HexusOpponentMenuIceCaps();

private:
	typedef HexusOpponentMenuBase super;
	static HexusOpponentMenuIceCaps* instance;
};
