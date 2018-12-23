#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentMinos : public HexusOpponentData
{
public:
	static HexusOpponentMinos* getInstance();

private:
	HexusOpponentMinos();
	~HexusOpponentMinos();

	static const std::string OpponentSaveKey;
	static HexusOpponentMinos* instance;
};
