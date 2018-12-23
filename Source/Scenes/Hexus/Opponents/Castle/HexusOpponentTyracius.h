#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

class HexusOpponentTyracius : public HexusOpponentData
{
public:
	static HexusOpponentTyracius* getInstance();

private:
	HexusOpponentTyracius();
	~HexusOpponentTyracius();

	static const std::string OpponentSaveKey;
	static HexusOpponentTyracius* instance;
};
