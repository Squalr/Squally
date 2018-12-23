#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentGoblinWarriorPig : public HexusOpponentData
{
public:
	static HexusOpponentGoblinWarriorPig* getInstance();

private:
	HexusOpponentGoblinWarriorPig();
	~HexusOpponentGoblinWarriorPig();

	static const std::string OpponentSaveKey;
	static HexusOpponentGoblinWarriorPig* instance;
};
