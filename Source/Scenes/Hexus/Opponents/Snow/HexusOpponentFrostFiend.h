#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentFrostFiend : public HexusOpponentData
{
public:
	static HexusOpponentFrostFiend* getInstance();

private:
	HexusOpponentFrostFiend();
	~HexusOpponentFrostFiend();

	static const std::string OpponentSaveKey;
	static HexusOpponentFrostFiend* instance;
};
