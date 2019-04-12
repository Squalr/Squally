#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

class HexusOpponentPuzzleTutorialA : public HexusOpponentData
{
public:
	static HexusOpponentPuzzleTutorialA* getInstance();

private:
	typedef HexusOpponentData super;
	HexusOpponentPuzzleTutorialA();
	~HexusOpponentPuzzleTutorialA();

	static const std::string OpponentSaveKey;
	static HexusOpponentPuzzleTutorialA* instance;
};
