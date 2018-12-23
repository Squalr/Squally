#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentMinotaur : public HexusOpponentData
{
public:
	static HexusOpponentMinotaur* getInstance();

private:
	HexusOpponentMinotaur();
	~HexusOpponentMinotaur();

	static const std::string OpponentSaveKey;
	static HexusOpponentMinotaur* instance;
};
