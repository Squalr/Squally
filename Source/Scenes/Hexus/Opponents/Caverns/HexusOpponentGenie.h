#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentGenie : public HexusOpponentData
{
public:
	static HexusOpponentGenie* getInstance();

private:
	HexusOpponentGenie();
	~HexusOpponentGenie();

	static const std::string OpponentSaveKey;
	static HexusOpponentGenie* instance;
};
