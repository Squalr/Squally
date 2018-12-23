#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentToben : public HexusOpponentData
{
public:
	static HexusOpponentToben* getInstance();

private:
	HexusOpponentToben();
	~HexusOpponentToben();

	static const std::string OpponentSaveKey;
	static HexusOpponentToben* instance;
};
