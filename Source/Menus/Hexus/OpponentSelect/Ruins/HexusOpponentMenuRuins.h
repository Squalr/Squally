#pragma once

#include "Menus/Hexus/OpponentSelect/HexusOpponentMenuBase.h"

class HexusOpponentMenuRuins : public HexusOpponentMenuBase
{
public:
	static void registerGlobalScene();

protected:
	HexusOpponentMenuRuins();
	~HexusOpponentMenuRuins();

private:
	static HexusOpponentMenuRuins* instance;
};
