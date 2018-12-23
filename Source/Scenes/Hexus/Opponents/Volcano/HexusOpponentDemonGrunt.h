#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentDemonGrunt : public HexusOpponentData
{
public:
	static HexusOpponentDemonGrunt* getInstance();

private:
	HexusOpponentDemonGrunt();
	~HexusOpponentDemonGrunt();

	static const std::string OpponentSaveKey;
	static HexusOpponentDemonGrunt* instance;
};
