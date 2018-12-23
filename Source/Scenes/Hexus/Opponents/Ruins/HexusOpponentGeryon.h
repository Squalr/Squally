#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentGeryon : public HexusOpponentData
{
public:
	static HexusOpponentGeryon* getInstance();

private:
	HexusOpponentGeryon();
	~HexusOpponentGeryon();

	static const std::string OpponentSaveKey;
	static HexusOpponentGeryon* instance;
};
