#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

class HexusOpponentTutorialC : public HexusOpponentData
{
public:
	static HexusOpponentTutorialC* getInstance();

private:
	HexusOpponentTutorialC();
	~HexusOpponentTutorialC();

	static const std::string OpponentSaveKey;
	static HexusOpponentTutorialC* instance;
};
