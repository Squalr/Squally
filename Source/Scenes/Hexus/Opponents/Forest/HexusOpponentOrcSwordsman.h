#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentOrcSwordsman : public HexusOpponentData
{
public:
	static HexusOpponentOrcSwordsman* getInstance();

private:
	HexusOpponentOrcSwordsman();
	~HexusOpponentOrcSwordsman();

	static const std::string OpponentSaveKey;
	static HexusOpponentOrcSwordsman* instance;
};
