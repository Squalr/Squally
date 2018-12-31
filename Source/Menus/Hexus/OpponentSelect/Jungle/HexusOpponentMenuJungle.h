#pragma once

#include "Menus/Hexus/OpponentSelect/HexusOpponentMenuBase.h"

class HexusOpponentMenuJungle : public HexusOpponentMenuBase
{
public:
	static void registerGlobalScene();

protected:
	HexusOpponentMenuJungle();
	~HexusOpponentMenuJungle();

private:
	typedef HexusOpponentMenuBase super;
	static HexusOpponentMenuJungle* instance;
};
