#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentCooper : public HexusOpponentData
{
public:
	static HexusOpponentCooper* getInstance();

private:
	HexusOpponentCooper();
	~HexusOpponentCooper();

	static const std::string OpponentSaveKey;
	static HexusOpponentCooper* instance;
};
