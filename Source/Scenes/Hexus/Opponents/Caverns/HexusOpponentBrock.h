#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

class HexusOpponentBrock : public HexusOpponentData
{
public:
	static HexusOpponentBrock* getInstance();

private:
	HexusOpponentBrock();
	~HexusOpponentBrock();

	static const std::string OpponentSaveKey;
	static HexusOpponentBrock* instance;
};
