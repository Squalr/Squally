#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentRaka : public HexusOpponentData
{
public:
	static HexusOpponentRaka* getInstance();

private:
	HexusOpponentRaka();
	~HexusOpponentRaka();

	static const std::string OpponentSaveKey;
	static HexusOpponentRaka* instance;
};
