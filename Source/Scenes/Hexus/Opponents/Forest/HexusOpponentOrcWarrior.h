#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentOrcWarrior : public HexusOpponentData
{
public:
	static HexusOpponentOrcWarrior* getInstance();

private:
	HexusOpponentOrcWarrior();
	~HexusOpponentOrcWarrior();

	static const std::string OpponentSaveKey;
	static HexusOpponentOrcWarrior* instance;
};
