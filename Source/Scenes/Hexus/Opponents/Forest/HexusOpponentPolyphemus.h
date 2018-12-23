#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentPolyphemus : public HexusOpponentData
{
public:
	static HexusOpponentPolyphemus* getInstance();

private:
	HexusOpponentPolyphemus();
	~HexusOpponentPolyphemus();

	static const std::string OpponentSaveKey;
	static HexusOpponentPolyphemus* instance;
};
