#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentDrak : public HexusOpponentData
{
public:
	static HexusOpponentDrak* getInstance();

private:
	HexusOpponentDrak();
	~HexusOpponentDrak();

	static const std::string OpponentSaveKey;
	static HexusOpponentDrak* instance;
};
