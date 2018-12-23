#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

class HexusOpponentLeroy : public HexusOpponentData
{
public:
	static HexusOpponentLeroy* getInstance();

private:
	HexusOpponentLeroy();
	~HexusOpponentLeroy();

	static const std::string OpponentSaveKey;
	static HexusOpponentLeroy* instance;
};
