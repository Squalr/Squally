#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentMildred : public HexusOpponentData
{
public:
	static HexusOpponentMildred* getInstance();

private:
	HexusOpponentMildred();
	~HexusOpponentMildred();

	static const std::string OpponentSaveKey;
	static HexusOpponentMildred* instance;
};
