#pragma once

#include "Scenes/Hexus/Menus/OpponentSelect/HexusOpponentMenuBase.h"

class HexusOpponentMenuLambdaCryptsPuzzle : public HexusOpponentMenuBase
{
public:
	static HexusOpponentMenuLambdaCryptsPuzzle* getInstance();

protected:
	HexusOpponentMenuLambdaCryptsPuzzle();
	~HexusOpponentMenuLambdaCryptsPuzzle();

private:
	typedef HexusOpponentMenuBase super;
	static HexusOpponentMenuLambdaCryptsPuzzle* instance;
};
