#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentRobin : public HexusOpponentData
{
public:
	static HexusOpponentRobin* getInstance();

private:
	HexusOpponentRobin();
	~HexusOpponentRobin();

	static const std::string OpponentSaveKey;
	static HexusOpponentRobin* instance;
};
