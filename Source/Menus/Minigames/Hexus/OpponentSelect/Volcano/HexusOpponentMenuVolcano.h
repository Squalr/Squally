#pragma once

#include "Menus/Minigames/Hexus/OpponentSelect/HexusOpponentMenuBase.h"

class HexusOpponentMenuVolcano : public HexusOpponentMenuBase
{
public:
	static void registerGlobalScene();

protected:
	HexusOpponentMenuVolcano();
	~HexusOpponentMenuVolcano();

private:
	static HexusOpponentMenuVolcano* instance;
};
