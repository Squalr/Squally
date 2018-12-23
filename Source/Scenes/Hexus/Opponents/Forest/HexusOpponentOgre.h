#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentOgre : public HexusOpponentData
{
public:
	static HexusOpponentOgre* getInstance();

private:
	HexusOpponentOgre();
	~HexusOpponentOgre();

	static const std::string OpponentSaveKey;
	static HexusOpponentOgre* instance;
};
