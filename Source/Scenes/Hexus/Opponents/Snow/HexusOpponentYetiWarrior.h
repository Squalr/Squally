#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentYetiWarrior : public HexusOpponentData
{
public:
	static HexusOpponentYetiWarrior* getInstance();

private:
	HexusOpponentYetiWarrior();
	~HexusOpponentYetiWarrior();

	static const std::string OpponentSaveKey;
	static HexusOpponentYetiWarrior* instance;
};
