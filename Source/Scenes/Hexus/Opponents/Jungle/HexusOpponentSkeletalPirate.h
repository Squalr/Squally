#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentSkeletalPirate : public HexusOpponentData
{
public:
	static HexusOpponentSkeletalPirate* getInstance();

private:
	HexusOpponentSkeletalPirate();
	~HexusOpponentSkeletalPirate();

	static const std::string OpponentSaveKey;
	static HexusOpponentSkeletalPirate* instance;
};
