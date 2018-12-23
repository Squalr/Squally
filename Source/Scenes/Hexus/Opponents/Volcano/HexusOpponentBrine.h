#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentBrine : public HexusOpponentData
{
public:
	static HexusOpponentBrine* getInstance();

private:
	HexusOpponentBrine();
	~HexusOpponentBrine();

	static const std::string OpponentSaveKey;
	static HexusOpponentBrine* instance;
};
