#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentMummyWarrior : public HexusOpponentData
{
public:
	static HexusOpponentMummyWarrior* getInstance();

private:
	HexusOpponentMummyWarrior();
	~HexusOpponentMummyWarrior();

	static const std::string OpponentSaveKey;
	static HexusOpponentMummyWarrior* instance;
};
