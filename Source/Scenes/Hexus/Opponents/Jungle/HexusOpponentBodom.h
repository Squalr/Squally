#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentBodom : public HexusOpponentData
{
public:
	static HexusOpponentBodom* getInstance();

private:
	HexusOpponentBodom();
	~HexusOpponentBodom();

	static const std::string OpponentSaveKey;
	static HexusOpponentBodom* instance;
};
