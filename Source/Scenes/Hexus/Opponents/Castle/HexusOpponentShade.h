#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

class HexusOpponentShade : public HexusOpponentData
{
public:
	static HexusOpponentShade* getInstance();

private:
	HexusOpponentShade();
	~HexusOpponentShade();

	static const std::string OpponentSaveKey;
	static HexusOpponentShade* instance;
};
