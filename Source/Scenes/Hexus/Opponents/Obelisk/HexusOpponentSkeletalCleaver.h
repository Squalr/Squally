#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentSkeletalCleaver : public HexusOpponentData
{
public:
	static HexusOpponentSkeletalCleaver* getInstance();

private:
	HexusOpponentSkeletalCleaver();
	~HexusOpponentSkeletalCleaver();

	static const std::string OpponentSaveKey;
	static HexusOpponentSkeletalCleaver* instance;
};
