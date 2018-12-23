#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentRoger : public HexusOpponentData
{
public:
	static HexusOpponentRoger* getInstance();

private:
	HexusOpponentRoger();
	~HexusOpponentRoger();

	static const std::string OpponentSaveKey;
	static HexusOpponentRoger* instance;
};
