#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentTigerMan : public HexusOpponentData
{
public:
	static HexusOpponentTigerMan* getInstance();

private:
	HexusOpponentTigerMan();
	~HexusOpponentTigerMan();

	static const std::string OpponentSaveKey;
	static HexusOpponentTigerMan* instance;
};
