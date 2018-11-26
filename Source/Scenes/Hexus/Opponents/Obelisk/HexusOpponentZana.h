#pragma once
#include "cocos2d.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentZana : public HexusOpponentData
{
public:
	static HexusOpponentZana* getInstance();

private:
	HexusOpponentZana();
	~HexusOpponentZana();

	static const std::string OpponentSaveKey;
	static HexusOpponentZana* instance;
};
