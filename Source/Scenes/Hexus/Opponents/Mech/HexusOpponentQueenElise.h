#pragma once
#include "cocos2d.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentQueenElise : public HexusOpponentData
{
public:
	static HexusOpponentQueenElise* getInstance();

private:
	HexusOpponentQueenElise();
	~HexusOpponentQueenElise();

	static const std::string OpponentSaveKey;
	static HexusOpponentQueenElise* instance;
};
