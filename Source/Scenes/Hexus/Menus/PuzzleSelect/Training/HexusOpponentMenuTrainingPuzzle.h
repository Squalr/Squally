#pragma once

#include "Scenes/Hexus/Menus/OpponentSelect/HexusOpponentMenuBase.h"

class HexusOpponentMenuTrainingPuzzle : public HexusOpponentMenuBase
{
public:
	static void registerGlobalScene();

protected:
	HexusOpponentMenuTrainingPuzzle();
	~HexusOpponentMenuTrainingPuzzle();

private:
	typedef HexusOpponentMenuBase super;
	static HexusOpponentMenuTrainingPuzzle* instance;
};
