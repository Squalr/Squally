#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentAnubisWarrior : public HexusOpponentData
{
public:
	static HexusOpponentAnubisWarrior* getInstance();

private:
	HexusOpponentAnubisWarrior();
	~HexusOpponentAnubisWarrior();

	static const std::string OpponentSaveKey;
	static HexusOpponentAnubisWarrior* instance;
};
