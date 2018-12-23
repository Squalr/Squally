#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

class HexusOpponentRaven : public HexusOpponentData
{
public:
	static HexusOpponentRaven* getInstance();

private:
	HexusOpponentRaven();
	~HexusOpponentRaven();

	static const std::string OpponentSaveKey;
	static HexusOpponentRaven* instance;
};
