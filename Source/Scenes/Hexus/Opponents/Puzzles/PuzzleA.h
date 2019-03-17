#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

class PuzzleA : public HexusOpponentData
{
public:
	static PuzzleA* getInstance();

private:
	typedef HexusOpponentData super;
	PuzzleA();
	~PuzzleA();

	static const std::string OpponentSaveKey;
	static PuzzleA* instance;
};
