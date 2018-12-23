#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

class HexusOpponentAgnes : public HexusOpponentData
{
public:
	static HexusOpponentAgnes* getInstance();

private:
	HexusOpponentAgnes();
	~HexusOpponentAgnes();

	static const std::string OpponentSaveKey;
	static HexusOpponentAgnes* instance;
};
