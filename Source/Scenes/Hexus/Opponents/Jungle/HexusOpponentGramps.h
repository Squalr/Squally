#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentGramps : public HexusOpponentData
{
public:
	static HexusOpponentGramps* getInstance();

private:
	HexusOpponentGramps();
	~HexusOpponentGramps();

	static const std::string OpponentSaveKey;
	static HexusOpponentGramps* instance;
};
