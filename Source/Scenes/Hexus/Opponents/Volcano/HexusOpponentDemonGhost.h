#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentDemonGhost : public HexusOpponentData
{
public:
	static HexusOpponentDemonGhost* getInstance();

private:
	HexusOpponentDemonGhost();
	~HexusOpponentDemonGhost();

	static const std::string OpponentSaveKey;
	static HexusOpponentDemonGhost* instance;
};
