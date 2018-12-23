#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentMedusa : public HexusOpponentData
{
public:
	static HexusOpponentMedusa* getInstance();

private:
	HexusOpponentMedusa();
	~HexusOpponentMedusa();

	static const std::string OpponentSaveKey;
	static HexusOpponentMedusa* instance;
};
