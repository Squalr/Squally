#pragma once
#include "cocos2d.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentXenon : public HexusOpponentData
{
public:
	static HexusOpponentXenon* getInstance();

private:
	HexusOpponentXenon();
	~HexusOpponentXenon();

	static const std::string OpponentSaveKey;
	static HexusOpponentXenon* instance;
};
