#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentRusty : public HexusOpponentData
{
public:
	static HexusOpponentRusty* getInstance();

private:
	HexusOpponentRusty();
	~HexusOpponentRusty();

	static const std::string OpponentSaveKey;
	static HexusOpponentRusty* instance;
};
