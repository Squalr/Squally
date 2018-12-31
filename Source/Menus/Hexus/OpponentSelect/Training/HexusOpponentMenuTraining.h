#pragma once

#include "Menus/Hexus/OpponentSelect/HexusOpponentMenuBase.h"

class HexusOpponentMenuTraining : public HexusOpponentMenuBase
{
public:
	static void registerGlobalScene();

protected:
	HexusOpponentMenuTraining();
	~HexusOpponentMenuTraining();

private:
	typedef HexusOpponentMenuBase super;
	static HexusOpponentMenuTraining* instance;
};
