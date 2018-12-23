#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentGorilla : public HexusOpponentData
{
public:
	static HexusOpponentGorilla* getInstance();

private:
	HexusOpponentGorilla();
	~HexusOpponentGorilla();

	static const std::string OpponentSaveKey;
	static HexusOpponentGorilla* instance;
};
