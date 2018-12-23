#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentOrcBomber : public HexusOpponentData
{
public:
	static HexusOpponentOrcBomber* getInstance();

private:
	HexusOpponentOrcBomber();
	~HexusOpponentOrcBomber();

	static const std::string OpponentSaveKey;
	static HexusOpponentOrcBomber* instance;
};
