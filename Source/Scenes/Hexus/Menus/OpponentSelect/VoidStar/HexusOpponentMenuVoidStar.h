#pragma once

#include "Scenes/Hexus/Menus/OpponentSelect/HexusOpponentMenuBase.h"

class HexusOpponentMenuVoidStar : public HexusOpponentMenuBase
{
public:
	static HexusOpponentMenuVoidStar* getInstance();

protected:
	HexusOpponentMenuVoidStar();
	~HexusOpponentMenuVoidStar();

private:
	typedef HexusOpponentMenuBase super;
	static HexusOpponentMenuVoidStar* instance;
};
