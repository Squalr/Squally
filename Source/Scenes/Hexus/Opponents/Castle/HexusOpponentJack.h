#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

class HexusOpponentJack : public HexusOpponentData
{
public:
	static HexusOpponentJack* getInstance();

private:
	HexusOpponentJack();
	~HexusOpponentJack();

	static const std::string OpponentSaveKey;
	static HexusOpponentJack* instance;
};
