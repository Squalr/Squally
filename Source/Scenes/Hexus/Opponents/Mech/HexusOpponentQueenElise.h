#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentQueenElise : public HexusOpponentData
{
public:
	static HexusOpponentQueenElise* getInstance();

private:
	HexusOpponentQueenElise();
	~HexusOpponentQueenElise();

	static const std::string OpponentSaveKey;
	static HexusOpponentQueenElise* instance;
};
