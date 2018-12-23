#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentOsiris : public HexusOpponentData
{
public:
	static HexusOpponentOsiris* getInstance();

private:
	HexusOpponentOsiris();
	~HexusOpponentOsiris();

	static const std::string OpponentSaveKey;
	static HexusOpponentOsiris* instance;
};
