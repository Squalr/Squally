#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentPan : public HexusOpponentData
{
public:
	static HexusOpponentPan* getInstance();

private:
	HexusOpponentPan();
	~HexusOpponentPan();

	static const std::string OpponentSaveKey;
	static HexusOpponentPan* instance;
};
