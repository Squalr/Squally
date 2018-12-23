#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentYsara : public HexusOpponentData
{
public:
	static HexusOpponentYsara* getInstance();

private:
	HexusOpponentYsara();
	~HexusOpponentYsara();

	static const std::string OpponentSaveKey;
	static HexusOpponentYsara* instance;
};
