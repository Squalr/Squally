#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentUndead : public HexusOpponentData
{
public:
	static HexusOpponentUndead* getInstance();

private:
	HexusOpponentUndead();
	~HexusOpponentUndead();

	static const std::string OpponentSaveKey;
	static HexusOpponentUndead* instance;
};
