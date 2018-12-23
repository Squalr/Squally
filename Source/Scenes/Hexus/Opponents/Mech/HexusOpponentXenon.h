#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentXenon : public HexusOpponentData
{
public:
	static HexusOpponentXenon* getInstance();

private:
	HexusOpponentXenon();
	~HexusOpponentXenon();

	static const std::string OpponentSaveKey;
	static HexusOpponentXenon* instance;
};
