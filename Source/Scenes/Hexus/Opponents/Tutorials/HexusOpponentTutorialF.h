#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

class HexusOpponentTutorialF : public HexusOpponentData
{
public:
	static HexusOpponentTutorialF* getInstance();

private:
	HexusOpponentTutorialF();
	~HexusOpponentTutorialF();

	static const std::string OpponentSaveKey;
	static HexusOpponentTutorialF* instance;
};
