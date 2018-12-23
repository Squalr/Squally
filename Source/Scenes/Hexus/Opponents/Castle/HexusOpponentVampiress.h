#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

class HexusOpponentVampiress : public HexusOpponentData
{
public:
	static HexusOpponentVampiress* getInstance();

private:
	HexusOpponentVampiress();
	~HexusOpponentVampiress();

	static const std::string OpponentSaveKey;
	static HexusOpponentVampiress* instance;
};
