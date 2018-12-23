#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentDemonWarrior : public HexusOpponentData
{
public:
	static HexusOpponentDemonWarrior* getInstance();

private:
	HexusOpponentDemonWarrior();
	~HexusOpponentDemonWarrior();

	static const std::string OpponentSaveKey;
	static HexusOpponentDemonWarrior* instance;
};
