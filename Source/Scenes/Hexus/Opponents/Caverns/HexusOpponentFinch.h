#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentFinch : public HexusOpponentData
{
public:
	static HexusOpponentFinch* getInstance();

private:
	HexusOpponentFinch();
	~HexusOpponentFinch();

	static const std::string OpponentSaveKey;
	static HexusOpponentFinch* instance;
};
