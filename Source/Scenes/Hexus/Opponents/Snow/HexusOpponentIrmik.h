#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentIrmik : public HexusOpponentData
{
public:
	static HexusOpponentIrmik* getInstance();

private:
	HexusOpponentIrmik();
	~HexusOpponentIrmik();

	static const std::string OpponentSaveKey;
	static HexusOpponentIrmik* instance;
};
