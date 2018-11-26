#pragma once
#include "cocos2d.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentSnowFiend : public HexusOpponentData
{
public:
	static HexusOpponentSnowFiend* getInstance();

private:
	HexusOpponentSnowFiend();
	~HexusOpponentSnowFiend();

	static const std::string OpponentSaveKey;
	static HexusOpponentSnowFiend* instance;
};
