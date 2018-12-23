#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentAppolo : public HexusOpponentData
{
public:
	static HexusOpponentAppolo* getInstance();

private:
	HexusOpponentAppolo();
	~HexusOpponentAppolo();

	static const std::string OpponentSaveKey;
	static HexusOpponentAppolo* instance;
};
