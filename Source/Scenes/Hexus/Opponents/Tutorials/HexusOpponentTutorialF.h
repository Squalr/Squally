#pragma once
#include "cocos2d.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"
#include "Scenes/Hexus/StateOverride.h"

using namespace cocos2d;

class HexusOpponentTutorialF : public HexusOpponentData
{
public:
	static HexusOpponentTutorialF* getInstance();

private:
	HexusOpponentTutorialF();
	~HexusOpponentTutorialF();

	static const std::string OpponentSaveKey;
	static HexusOpponentTutorialF* instance;
};
