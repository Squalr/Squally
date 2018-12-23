#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentTikiGolem : public HexusOpponentData
{
public:
	static HexusOpponentTikiGolem* getInstance();

private:
	HexusOpponentTikiGolem();
	~HexusOpponentTikiGolem();

	static const std::string OpponentSaveKey;
	static HexusOpponentTikiGolem* instance;
};
