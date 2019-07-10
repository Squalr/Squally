#pragma once

#include "Scenes/Hexus/Menus/OpponentSelect/HexusOpponentMenuBase.h"

class HexusOpponentMenuLambdaCrypts : public HexusOpponentMenuBase
{
public:
	static HexusOpponentMenuLambdaCrypts* getInstance();

protected:
	HexusOpponentMenuLambdaCrypts();
	~HexusOpponentMenuLambdaCrypts();

private:
	typedef HexusOpponentMenuBase super;
	static HexusOpponentMenuLambdaCrypts* instance;
};
