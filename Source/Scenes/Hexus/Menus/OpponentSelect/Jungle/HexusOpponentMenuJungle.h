#pragma once

#include "Scenes/Hexus/Menus/OpponentSelect/HexusOpponentMenuBase.h"

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
