#pragma once

#include "Scenes/Hexus/Menus/OpponentSelect/HexusOpponentMenuBase.h"

class HexusOpponentMenuUnderflowRuinsPuzzle : public HexusOpponentMenuBase
{
public:
	static HexusOpponentMenuUnderflowRuinsPuzzle* getInstance();

protected:
	HexusOpponentMenuUnderflowRuinsPuzzle();
	~HexusOpponentMenuUnderflowRuinsPuzzle();

private:
	typedef HexusOpponentMenuBase super;
	static HexusOpponentMenuUnderflowRuinsPuzzle* instance;
};
