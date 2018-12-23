#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentUrsula : public HexusOpponentData
{
public:
	static HexusOpponentUrsula* getInstance();

private:
	HexusOpponentUrsula();
	~HexusOpponentUrsula();

	static const std::string OpponentSaveKey;
	static HexusOpponentUrsula* instance;
};
