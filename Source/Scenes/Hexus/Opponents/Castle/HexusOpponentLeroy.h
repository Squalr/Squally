#pragma once
#include "cocos2d.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentLeroy : public HexusOpponentData
{
public:
	static HexusOpponentLeroy* getInstance();

private:
	HexusOpponentLeroy();
	~HexusOpponentLeroy();

	static const std::string OpponentSaveKey;
	static HexusOpponentLeroy* instance;
};
