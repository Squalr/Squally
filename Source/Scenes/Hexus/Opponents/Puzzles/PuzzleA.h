#pragma once
#include "cocos2d.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"
#include "Scenes/Hexus/StateOverride.h"

using namespace cocos2d;

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
