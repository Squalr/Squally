#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentCookie : public HexusOpponentData
{
public:
	static HexusOpponentCookie* getInstance();

private:
	HexusOpponentCookie();
	~HexusOpponentCookie();

	static const std::string OpponentSaveKey;
	static HexusOpponentCookie* instance;
};
