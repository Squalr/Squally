#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentPiper : public HexusOpponentData
{
public:
	static HexusOpponentPiper* getInstance();

private:
	HexusOpponentPiper();
	~HexusOpponentPiper();

	static const std::string OpponentSaveKey;
	static HexusOpponentPiper* instance;
};
