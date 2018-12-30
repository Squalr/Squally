#pragma once

#include "Menus/Hexus/OpponentSelect/HexusOpponentMenuBase.h"

class HexusOpponentMenuForest : public HexusOpponentMenuBase
{
public:
	static void registerGlobalScene();

protected:
	HexusOpponentMenuForest();
	~HexusOpponentMenuForest();

private:
	static HexusOpponentMenuForest* instance;
};
