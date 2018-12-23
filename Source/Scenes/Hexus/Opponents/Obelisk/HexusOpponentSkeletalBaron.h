#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentSkeletalBaron : public HexusOpponentData
{
public:
	static HexusOpponentSkeletalBaron* getInstance();

private:
	HexusOpponentSkeletalBaron();
	~HexusOpponentSkeletalBaron();

	static const std::string OpponentSaveKey;
	static HexusOpponentSkeletalBaron* instance;
};
