#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentThor : public HexusOpponentData
{
public:
	static HexusOpponentThor* getInstance();

private:
	HexusOpponentThor();
	~HexusOpponentThor();

	static const std::string OpponentSaveKey;
	static HexusOpponentThor* instance;
};
