#pragma once

#include "Menus/Hexus/OpponentSelect/HexusOpponentMenuBase.h"

class HexusOpponentMenuVolcano : public HexusOpponentMenuBase
{
public:
	static void registerGlobalScene();

protected:
	HexusOpponentMenuVolcano();
	~HexusOpponentMenuVolcano();

private:
	typedef HexusOpponentMenuBase super;
	static HexusOpponentMenuVolcano* instance;
};
