#pragma once
#include "cocos2d.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentCypress : public HexusOpponentData
{
public:
	static HexusOpponentCypress* getInstance();

private:
	HexusOpponentCypress();
	~HexusOpponentCypress();

	static const std::string OpponentSaveKey;
	static HexusOpponentCypress* instance;
};
