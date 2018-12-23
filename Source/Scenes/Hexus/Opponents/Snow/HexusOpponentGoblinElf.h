#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentGoblinElf : public HexusOpponentData
{
public:
	static HexusOpponentGoblinElf* getInstance();

private:
	HexusOpponentGoblinElf();
	~HexusOpponentGoblinElf();

	static const std::string OpponentSaveKey;
	static HexusOpponentGoblinElf* instance;
};
