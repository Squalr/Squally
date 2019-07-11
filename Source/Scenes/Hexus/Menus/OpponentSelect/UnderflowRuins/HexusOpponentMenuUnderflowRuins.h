#pragma once

#include "Scenes/Hexus/Menus/OpponentSelect/HexusOpponentMenuBase.h"

class HexusOpponentMenuUnderflowRuins : public HexusOpponentMenuBase
{
public:
	static HexusOpponentMenuUnderflowRuins* getInstance();

protected:
	HexusOpponentMenuUnderflowRuins();
	~HexusOpponentMenuUnderflowRuins();

private:
	typedef HexusOpponentMenuBase super;
	static HexusOpponentMenuUnderflowRuins* instance;
};
