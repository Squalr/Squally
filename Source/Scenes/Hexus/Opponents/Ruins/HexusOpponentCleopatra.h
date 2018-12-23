#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentCleopatra : public HexusOpponentData
{
public:
	static HexusOpponentCleopatra* getInstance();

private:
	HexusOpponentCleopatra();
	~HexusOpponentCleopatra();

	static const std::string OpponentSaveKey;
	static HexusOpponentCleopatra* instance;
};
