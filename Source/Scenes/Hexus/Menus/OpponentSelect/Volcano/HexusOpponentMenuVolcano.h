#pragma once

#include "Scenes/Hexus/Menus/OpponentSelect/HexusOpponentMenuBase.h"

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
