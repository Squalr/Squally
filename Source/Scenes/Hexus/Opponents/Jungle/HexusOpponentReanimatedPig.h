#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentReanimatedPig : public HexusOpponentData
{
public:
	static HexusOpponentReanimatedPig* getInstance();

private:
	HexusOpponentReanimatedPig();
	~HexusOpponentReanimatedPig();

	static const std::string OpponentSaveKey;
	static HexusOpponentReanimatedPig* instance;
};
