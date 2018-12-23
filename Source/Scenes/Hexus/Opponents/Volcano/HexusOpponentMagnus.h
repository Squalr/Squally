#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentMagnus : public HexusOpponentData
{
public:
	static HexusOpponentMagnus* getInstance();

private:
	HexusOpponentMagnus();
	~HexusOpponentMagnus();

	static const std::string OpponentSaveKey;
	static HexusOpponentMagnus* instance;
};
