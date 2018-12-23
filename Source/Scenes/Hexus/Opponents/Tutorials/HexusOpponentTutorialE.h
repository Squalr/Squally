#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

class HexusOpponentTutorialE : public HexusOpponentData
{
public:
	static HexusOpponentTutorialE* getInstance();

private:
	HexusOpponentTutorialE();
	~HexusOpponentTutorialE();

	static const std::string OpponentSaveKey;
	static HexusOpponentTutorialE* instance;
};
