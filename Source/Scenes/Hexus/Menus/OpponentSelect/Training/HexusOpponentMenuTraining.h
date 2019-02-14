#pragma once

#include "Scenes/Hexus/Menus/OpponentSelect/HexusOpponentMenuBase.h"

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
