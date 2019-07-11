#pragma once

#include "Scenes/Hexus/Menus/OpponentSelect/HexusOpponentMenuBase.h"

class HexusOpponentMenuEndianForest : public HexusOpponentMenuBase
{
public:
	static HexusOpponentMenuEndianForest* getInstance();

protected:
	HexusOpponentMenuEndianForest();
	~HexusOpponentMenuEndianForest();

private:
	typedef HexusOpponentMenuBase super;
	static HexusOpponentMenuEndianForest* instance;
};
