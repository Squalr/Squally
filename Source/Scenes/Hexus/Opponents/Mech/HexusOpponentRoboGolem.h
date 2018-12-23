#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentRoboGolem : public HexusOpponentData
{
public:
	static HexusOpponentRoboGolem* getInstance();

private:
	HexusOpponentRoboGolem();
	~HexusOpponentRoboGolem();

	static const std::string OpponentSaveKey;
	static HexusOpponentRoboGolem* instance;
};
