#pragma once

#include "Scenes/Hexus/Menus/OpponentSelect/HexusOpponentMenuBase.h"

class HexusOpponentMenuObelisk : public HexusOpponentMenuBase
{
public:
	static void registerGlobalScene();

protected:
	HexusOpponentMenuObelisk();
	~HexusOpponentMenuObelisk();

private:	
	typedef HexusOpponentMenuBase super;
	static HexusOpponentMenuObelisk* instance;
};
