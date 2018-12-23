#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentAsh : public HexusOpponentData
{
public:
	static HexusOpponentAsh* getInstance();

private:
	HexusOpponentAsh();
	~HexusOpponentAsh();

	static const std::string OpponentSaveKey;
	static HexusOpponentAsh* instance;
};
