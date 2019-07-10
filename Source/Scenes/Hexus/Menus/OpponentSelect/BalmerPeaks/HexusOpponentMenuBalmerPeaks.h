#pragma once

#include "Scenes/Hexus/Menus/OpponentSelect/HexusOpponentMenuBase.h"

class HexusOpponentMenuBalmerPeaks : public HexusOpponentMenuBase
{
public:
	static HexusOpponentMenuBalmerPeaks* getInstance();

protected:
	HexusOpponentMenuBalmerPeaks();
	~HexusOpponentMenuBalmerPeaks();

private:
	typedef HexusOpponentMenuBase super;
	static HexusOpponentMenuBalmerPeaks* instance;
};
