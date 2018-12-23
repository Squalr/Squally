#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentViper : public HexusOpponentData
{
public:
	static HexusOpponentViper* getInstance();

private:
	HexusOpponentViper();
	~HexusOpponentViper();

	static const std::string OpponentSaveKey;
	static HexusOpponentViper* instance;
};
