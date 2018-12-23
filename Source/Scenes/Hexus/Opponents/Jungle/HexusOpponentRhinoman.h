#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentRhinoman : public HexusOpponentData
{
public:
	static HexusOpponentRhinoman* getInstance();

private:
	HexusOpponentRhinoman();
	~HexusOpponentRhinoman();

	static const std::string OpponentSaveKey;
	static HexusOpponentRhinoman* instance;
};
