#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

class HexusOpponentWraith : public HexusOpponentData
{
public:
	static HexusOpponentWraith* getInstance();

private:
	HexusOpponentWraith();
	~HexusOpponentWraith();

	static const std::string OpponentSaveKey;
	static HexusOpponentWraith* instance;
};
