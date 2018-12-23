#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentJasper : public HexusOpponentData
{
public:
	static HexusOpponentJasper* getInstance();

private:
	HexusOpponentJasper();
	~HexusOpponentJasper();

	static const std::string OpponentSaveKey;
	static HexusOpponentJasper* instance;
};
