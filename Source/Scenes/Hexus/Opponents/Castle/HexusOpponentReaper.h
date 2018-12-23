#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

class HexusOpponentReaper : public HexusOpponentData
{
public:
	static HexusOpponentReaper* getInstance();

private:
	HexusOpponentReaper();
	~HexusOpponentReaper();

	static const std::string OpponentSaveKey;
	static HexusOpponentReaper* instance;
};
