#pragma once
#include "cocos2d.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentExecutioner : public HexusOpponentData
{
public:
	static HexusOpponentExecutioner* getInstance();

private:
	HexusOpponentExecutioner();
	~HexusOpponentExecutioner();

	static const std::string OpponentSaveKey;
	static HexusOpponentExecutioner* instance;
};
