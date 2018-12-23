#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentJohann : public HexusOpponentData
{
public:
	static HexusOpponentJohann* getInstance();

private:
	HexusOpponentJohann();
	~HexusOpponentJohann();

	static const std::string OpponentSaveKey;
	static HexusOpponentJohann* instance;
};
