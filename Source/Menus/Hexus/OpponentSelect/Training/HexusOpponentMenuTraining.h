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
	static HexusOpponentMenuTraining* instance;
};
