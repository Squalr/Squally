#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

class HexusOpponentTutorialD : public HexusOpponentData
{
public:
	static HexusOpponentTutorialD* getInstance();

private:
	HexusOpponentTutorialD();
	~HexusOpponentTutorialD();

	static const std::string OpponentSaveKey;
	static HexusOpponentTutorialD* instance;
};
