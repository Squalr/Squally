#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentAphrodite : public HexusOpponentData
{
public:
	static HexusOpponentAphrodite* getInstance();

private:
	HexusOpponentAphrodite();
	~HexusOpponentAphrodite();

	static const std::string OpponentSaveKey;
	static HexusOpponentAphrodite* instance;
};
