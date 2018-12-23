#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentJuniper : public HexusOpponentData
{
public:
	static HexusOpponentJuniper* getInstance();

private:
	HexusOpponentJuniper();
	~HexusOpponentJuniper();

	static const std::string OpponentSaveKey;
	static HexusOpponentJuniper* instance;
};
