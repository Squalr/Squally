#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

class HexusOpponentErlic : public HexusOpponentData
{
public:
	static HexusOpponentErlic* getInstance();

private:
	HexusOpponentErlic();
	~HexusOpponentErlic();

	static const std::string OpponentSaveKey;
	static HexusOpponentErlic* instance;
};
