#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentPenguinGrunt : public HexusOpponentData
{
public:
	static HexusOpponentPenguinGrunt* getInstance();

private:
	HexusOpponentPenguinGrunt();
	~HexusOpponentPenguinGrunt();

	static const std::string OpponentSaveKey;
	static HexusOpponentPenguinGrunt* instance;
};
