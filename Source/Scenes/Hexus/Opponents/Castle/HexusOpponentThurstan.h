#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

class HexusOpponentThurstan : public HexusOpponentData
{
public:
	static HexusOpponentThurstan* getInstance();

private:
	HexusOpponentThurstan();
	~HexusOpponentThurstan();

	static const std::string OpponentSaveKey;
	static HexusOpponentThurstan* instance;
};
