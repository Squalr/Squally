#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentPenguinWarrior : public HexusOpponentData
{
public:
	static HexusOpponentPenguinWarrior* getInstance();

private:
	HexusOpponentPenguinWarrior();
	~HexusOpponentPenguinWarrior();

	static const std::string OpponentSaveKey;
	static HexusOpponentPenguinWarrior* instance;
};
