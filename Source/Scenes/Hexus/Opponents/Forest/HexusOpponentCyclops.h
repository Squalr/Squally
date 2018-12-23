#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentCyclops : public HexusOpponentData
{
public:
	static HexusOpponentCyclops* getInstance();

private:
	HexusOpponentCyclops();
	~HexusOpponentCyclops();

	static const std::string OpponentSaveKey;
	static HexusOpponentCyclops* instance;
};
