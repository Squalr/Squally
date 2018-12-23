#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentTroll : public HexusOpponentData
{
public:
	static HexusOpponentTroll* getInstance();

private:
	HexusOpponentTroll();
	~HexusOpponentTroll();

	static const std::string OpponentSaveKey;
	static HexusOpponentTroll* instance;
};
