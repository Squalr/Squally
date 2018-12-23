#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentLioness : public HexusOpponentData
{
public:
	static HexusOpponentLioness* getInstance();

private:
	HexusOpponentLioness();
	~HexusOpponentLioness();

	static const std::string OpponentSaveKey;
	static HexusOpponentLioness* instance;
};
