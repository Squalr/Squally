#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentDemonDragon : public HexusOpponentData
{
public:
	static HexusOpponentDemonDragon* getInstance();

private:
	HexusOpponentDemonDragon();
	~HexusOpponentDemonDragon();

	static const std::string OpponentSaveKey;
	static HexusOpponentDemonDragon* instance;
};
