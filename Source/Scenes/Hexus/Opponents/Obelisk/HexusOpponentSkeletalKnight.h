#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentSkeletalKnight : public HexusOpponentData
{
public:
	static HexusOpponentSkeletalKnight* getInstance();

private:
	HexusOpponentSkeletalKnight();
	~HexusOpponentSkeletalKnight();

	static const std::string OpponentSaveKey;
	static HexusOpponentSkeletalKnight* instance;
};
