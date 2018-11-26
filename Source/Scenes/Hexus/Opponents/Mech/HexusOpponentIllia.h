#pragma once
#include "cocos2d.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentIllia : public HexusOpponentData
{
public:
	static HexusOpponentIllia* getInstance();

private:
	HexusOpponentIllia();
	~HexusOpponentIllia();

	static const std::string OpponentSaveKey;
	static HexusOpponentIllia* instance;
};
