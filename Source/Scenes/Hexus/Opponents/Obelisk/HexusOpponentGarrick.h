#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentGarrick : public HexusOpponentData
{
public:
	static HexusOpponentGarrick* getInstance();

private:
	HexusOpponentGarrick();
	~HexusOpponentGarrick();

	static const std::string OpponentSaveKey;
	static HexusOpponentGarrick* instance;
};
