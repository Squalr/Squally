#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentSkeletalWarrior : public HexusOpponentData
{
public:
	static HexusOpponentSkeletalWarrior* getInstance();

private:
	HexusOpponentSkeletalWarrior();
	~HexusOpponentSkeletalWarrior();

	static const std::string OpponentSaveKey;
	static HexusOpponentSkeletalWarrior* instance;
};
