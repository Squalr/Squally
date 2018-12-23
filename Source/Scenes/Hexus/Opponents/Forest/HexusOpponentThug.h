#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentThug : public HexusOpponentData
{
public:
	static HexusOpponentThug* getInstance();

private:
	HexusOpponentThug();
	~HexusOpponentThug();

	static const std::string OpponentSaveKey;
	static HexusOpponentThug* instance;
};
