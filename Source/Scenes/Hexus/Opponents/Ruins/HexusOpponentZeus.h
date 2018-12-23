#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentZeus : public HexusOpponentData
{
public:
	static HexusOpponentZeus* getInstance();

private:
	HexusOpponentZeus();
	~HexusOpponentZeus();

	static const std::string OpponentSaveKey;
	static HexusOpponentZeus* instance;
};
