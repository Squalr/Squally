#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentOlive : public HexusOpponentData
{
public:
	static HexusOpponentOlive* getInstance();

private:
	HexusOpponentOlive();
	~HexusOpponentOlive();

	static const std::string OpponentSaveKey;
	static HexusOpponentOlive* instance;
};
