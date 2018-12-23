#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentThion : public HexusOpponentData
{
public:
	static HexusOpponentThion* getInstance();

private:
	HexusOpponentThion();
	~HexusOpponentThion();

	static const std::string OpponentSaveKey;
	static HexusOpponentThion* instance;
};
