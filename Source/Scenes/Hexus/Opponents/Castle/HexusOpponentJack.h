#pragma once
#include "cocos2d.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentJack : public HexusOpponentData
{
public:
	static HexusOpponentJack* getInstance();

private:
	HexusOpponentJack();
	~HexusOpponentJack();

	static const std::string OpponentSaveKey;
	static HexusOpponentJack* instance;
};
