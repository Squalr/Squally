#pragma once

#include "Scenes/Hexus/Menus/OpponentSelect/HexusOpponentMenuBase.h"

class HexusOpponentMenuTraining : public HexusOpponentMenuBase
{
public:
	static HexusOpponentMenuTraining* getInstance();

protected:
	HexusOpponentMenuTraining();
	~HexusOpponentMenuTraining();

private:
	typedef HexusOpponentMenuBase super;
	static HexusOpponentMenuTraining* instance;
};
