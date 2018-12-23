#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentLycan : public HexusOpponentData
{
public:
	static HexusOpponentLycan* getInstance();

private:
	HexusOpponentLycan();
	~HexusOpponentLycan();

	static const std::string OpponentSaveKey;
	static HexusOpponentLycan* instance;
};
