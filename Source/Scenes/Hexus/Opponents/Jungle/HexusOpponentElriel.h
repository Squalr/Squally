#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentElriel : public HexusOpponentData
{
public:
	static HexusOpponentElriel* getInstance();

private:
	HexusOpponentElriel();
	~HexusOpponentElriel();

	static const std::string OpponentSaveKey;
	static HexusOpponentElriel* instance;
};
