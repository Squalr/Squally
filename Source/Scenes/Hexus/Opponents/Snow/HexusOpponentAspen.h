#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentAspen : public HexusOpponentData
{
public:
	static HexusOpponentAspen* getInstance();

private:
	HexusOpponentAspen();
	~HexusOpponentAspen();

	static const std::string OpponentSaveKey;
	static HexusOpponentAspen* instance;
};
