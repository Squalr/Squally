#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

class HexusOpponentMerlin : public HexusOpponentData
{
public:
	static HexusOpponentMerlin* getInstance();

private:
	HexusOpponentMerlin();
	~HexusOpponentMerlin();

	static const std::string OpponentSaveKey;
	static HexusOpponentMerlin* instance;
};
