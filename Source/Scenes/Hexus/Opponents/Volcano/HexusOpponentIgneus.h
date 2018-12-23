#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentIgneus : public HexusOpponentData
{
public:
	static HexusOpponentIgneus* getInstance();

private:
	HexusOpponentIgneus();
	~HexusOpponentIgneus();

	static const std::string OpponentSaveKey;
	static HexusOpponentIgneus* instance;
};
