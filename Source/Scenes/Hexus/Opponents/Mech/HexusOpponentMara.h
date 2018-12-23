#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentMara : public HexusOpponentData
{
public:
	static HexusOpponentMara* getInstance();

private:
	HexusOpponentMara();
	~HexusOpponentMara();

	static const std::string OpponentSaveKey;
	static HexusOpponentMara* instance;
};
