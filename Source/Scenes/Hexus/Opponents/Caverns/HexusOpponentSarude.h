#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentSarude : public HexusOpponentData
{
public:
	static HexusOpponentSarude* getInstance();

private:
	HexusOpponentSarude();
	~HexusOpponentSarude();

	static const std::string OpponentSaveKey;
	static HexusOpponentSarude* instance;
};
