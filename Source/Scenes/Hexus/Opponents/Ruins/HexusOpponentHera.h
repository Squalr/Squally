#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentHera : public HexusOpponentData
{
public:
	static HexusOpponentHera* getInstance();

private:
	HexusOpponentHera();
	~HexusOpponentHera();

	static const std::string OpponentSaveKey;
	static HexusOpponentHera* instance;
};
