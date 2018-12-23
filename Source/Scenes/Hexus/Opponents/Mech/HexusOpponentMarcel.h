#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentMarcel : public HexusOpponentData
{
public:
	static HexusOpponentMarcel* getInstance();

private:
	HexusOpponentMarcel();
	~HexusOpponentMarcel();

	static const std::string OpponentSaveKey;
	static HexusOpponentMarcel* instance;
};
