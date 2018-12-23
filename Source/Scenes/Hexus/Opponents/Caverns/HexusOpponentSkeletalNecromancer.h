#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentSkeletalNecromancer : public HexusOpponentData
{
public:
	static HexusOpponentSkeletalNecromancer* getInstance();

private:
	HexusOpponentSkeletalNecromancer();
	~HexusOpponentSkeletalNecromancer();

	static const std::string OpponentSaveKey;
	static HexusOpponentSkeletalNecromancer* instance;
};
