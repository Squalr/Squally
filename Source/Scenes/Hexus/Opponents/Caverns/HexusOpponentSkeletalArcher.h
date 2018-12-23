#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentSkeletalArcher : public HexusOpponentData
{
public:
	static HexusOpponentSkeletalArcher* getInstance();

private:
	HexusOpponentSkeletalArcher();
	~HexusOpponentSkeletalArcher();

	static const std::string OpponentSaveKey;
	static HexusOpponentSkeletalArcher* instance;
};
