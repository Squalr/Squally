#pragma once
#include "cocos2d.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentThug : public HexusOpponentData
{
public:
	static HexusOpponentThug* getInstance();

private:
	HexusOpponentThug();
	~HexusOpponentThug();

	static const std::string OpponentSaveKey;
	static HexusOpponentThug* instance;
};
