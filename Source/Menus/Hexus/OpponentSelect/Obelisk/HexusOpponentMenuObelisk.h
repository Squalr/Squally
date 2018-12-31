#pragma once

#include "Menus/Hexus/OpponentSelect/HexusOpponentMenuBase.h"

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
