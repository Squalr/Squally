#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

class HexusOpponentTutorialA : public HexusOpponentData
{
public:
	static HexusOpponentTutorialA* getInstance();

private:
	typedef HexusOpponentData super;
	HexusOpponentTutorialA();
	~HexusOpponentTutorialA();

	static const std::string OpponentSaveKey;
	static HexusOpponentTutorialA* instance;
};
