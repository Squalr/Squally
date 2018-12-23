#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentOrcGrunt : public HexusOpponentData
{
public:
	static HexusOpponentOrcGrunt* getInstance();

private:
	HexusOpponentOrcGrunt();
	~HexusOpponentOrcGrunt();

	static const std::string OpponentSaveKey;
	static HexusOpponentOrcGrunt* instance;
};
