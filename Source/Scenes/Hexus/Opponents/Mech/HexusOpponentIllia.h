#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentIllia : public HexusOpponentData
{
public:
	static HexusOpponentIllia* getInstance();

private:
	HexusOpponentIllia();
	~HexusOpponentIllia();

	static const std::string OpponentSaveKey;
	static HexusOpponentIllia* instance;
};
