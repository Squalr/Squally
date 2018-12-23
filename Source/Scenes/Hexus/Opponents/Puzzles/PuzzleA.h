#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

class PuzzleA : public HexusOpponentData
{
public:
	static PuzzleA* getInstance();

private:
	PuzzleA();
	~PuzzleA();

	static const std::string OpponentSaveKey;
	static PuzzleA* instance;
};
