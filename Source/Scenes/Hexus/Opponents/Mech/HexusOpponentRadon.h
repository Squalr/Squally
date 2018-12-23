#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentRadon : public HexusOpponentData
{
public:
	static HexusOpponentRadon* getInstance();

private:
	HexusOpponentRadon();
	~HexusOpponentRadon();

	static const std::string OpponentSaveKey;
	static HexusOpponentRadon* instance;
};
