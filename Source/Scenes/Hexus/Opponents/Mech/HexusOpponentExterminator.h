#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentExterminator : public HexusOpponentData
{
public:
	static HexusOpponentExterminator* getInstance();

private:
	HexusOpponentExterminator();
	~HexusOpponentExterminator();

	static const std::string OpponentSaveKey;
	static HexusOpponentExterminator* instance;
};
