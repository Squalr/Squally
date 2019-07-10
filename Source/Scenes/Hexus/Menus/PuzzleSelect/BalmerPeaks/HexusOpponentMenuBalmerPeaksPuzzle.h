#pragma once

#include "Scenes/Hexus/Menus/OpponentSelect/HexusOpponentMenuBase.h"

class HexusOpponentMenuBalmerPeaksPuzzle : public HexusOpponentMenuBase
{
public:
	static HexusOpponentMenuBalmerPeaksPuzzle* getInstance();

protected:
	HexusOpponentMenuBalmerPeaksPuzzle();
	~HexusOpponentMenuBalmerPeaksPuzzle();

private:
	typedef HexusOpponentMenuBase super;
	static HexusOpponentMenuBalmerPeaksPuzzle* instance;
};
