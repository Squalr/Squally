#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentAmelia : public HexusOpponentData
{
public:
	static HexusOpponentAmelia* getInstance();

private:
	HexusOpponentAmelia();
	~HexusOpponentAmelia();

	static const std::string OpponentSaveKey;
	static HexusOpponentAmelia* instance;
};
