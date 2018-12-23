#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

class HexusOpponentExecutioner : public HexusOpponentData
{
public:
	static HexusOpponentExecutioner* getInstance();

private:
	HexusOpponentExecutioner();
	~HexusOpponentExecutioner();

	static const std::string OpponentSaveKey;
	static HexusOpponentExecutioner* instance;
};
