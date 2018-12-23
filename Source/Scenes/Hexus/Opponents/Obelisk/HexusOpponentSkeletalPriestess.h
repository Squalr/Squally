#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentSkeletalPriestess : public HexusOpponentData
{
public:
	static HexusOpponentSkeletalPriestess* getInstance();

private:
	HexusOpponentSkeletalPriestess();
	~HexusOpponentSkeletalPriestess();

	static const std::string OpponentSaveKey;
	static HexusOpponentSkeletalPriestess* instance;
};
