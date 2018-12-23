#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentCryogen : public HexusOpponentData
{
public:
	static HexusOpponentCryogen* getInstance();

private:
	HexusOpponentCryogen();
	~HexusOpponentCryogen();

	static const std::string OpponentSaveKey;
	static HexusOpponentCryogen* instance;
};
