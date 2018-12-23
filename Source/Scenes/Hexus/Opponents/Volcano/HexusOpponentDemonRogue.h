#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentDemonRogue : public HexusOpponentData
{
public:
	static HexusOpponentDemonRogue* getInstance();

private:
	HexusOpponentDemonRogue();
	~HexusOpponentDemonRogue();

	static const std::string OpponentSaveKey;
	static HexusOpponentDemonRogue* instance;
};
