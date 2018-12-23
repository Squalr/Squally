#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

class HexusOpponentRogas : public HexusOpponentData
{
public:
	static HexusOpponentRogas* getInstance();

private:
	HexusOpponentRogas();
	~HexusOpponentRogas();

	static const std::string OpponentSaveKey;
	static HexusOpponentRogas* instance;
};
