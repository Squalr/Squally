#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentAster : public HexusOpponentData
{
public:
	static HexusOpponentAster* getInstance();

private:
	HexusOpponentAster();
	~HexusOpponentAster();

	static const std::string OpponentSaveKey;
	static HexusOpponentAster* instance;
};
