#pragma once
#include "cocos2d.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentThion : public HexusOpponentData
{
public:
	static HexusOpponentThion* getInstance();

private:
	HexusOpponentThion();
	~HexusOpponentThion();

	static const std::string OpponentSaveKey;
	static HexusOpponentThion* instance;
};
