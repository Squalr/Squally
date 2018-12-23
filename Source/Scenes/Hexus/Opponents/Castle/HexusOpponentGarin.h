#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

class HexusOpponentGarin : public HexusOpponentData
{
public:
	static HexusOpponentGarin* getInstance();

private:
	HexusOpponentGarin();
	~HexusOpponentGarin();

	static const std::string OpponentSaveKey;
	static HexusOpponentGarin* instance;
};
