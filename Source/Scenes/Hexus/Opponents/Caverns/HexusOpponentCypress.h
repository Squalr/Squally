#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

class HexusOpponentCypress : public HexusOpponentData
{
public:
	static HexusOpponentCypress* getInstance();

private:
	HexusOpponentCypress();
	~HexusOpponentCypress();

	static const std::string OpponentSaveKey;
	static HexusOpponentCypress* instance;
};
