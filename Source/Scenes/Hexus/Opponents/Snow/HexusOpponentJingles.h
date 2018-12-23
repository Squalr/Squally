#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentJingles : public HexusOpponentData
{
public:
	static HexusOpponentJingles* getInstance();

private:
	HexusOpponentJingles();
	~HexusOpponentJingles();

	static const std::string OpponentSaveKey;
	static HexusOpponentJingles* instance;
};
