#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

class HexusOpponentTutorialB : public HexusOpponentData
{
public:
	static HexusOpponentTutorialB* getInstance();

private:
	HexusOpponentTutorialB();
	~HexusOpponentTutorialB();

	static const std::string OpponentSaveKey;
	static HexusOpponentTutorialB* instance;
};
