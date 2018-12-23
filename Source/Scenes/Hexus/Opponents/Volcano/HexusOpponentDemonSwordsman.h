#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentDemonSwordsman : public HexusOpponentData
{
public:
	static HexusOpponentDemonSwordsman* getInstance();

private:
	HexusOpponentDemonSwordsman();
	~HexusOpponentDemonSwordsman();

	static const std::string OpponentSaveKey;
	static HexusOpponentDemonSwordsman* instance;
};
