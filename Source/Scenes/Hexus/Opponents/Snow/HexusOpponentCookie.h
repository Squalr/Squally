#pragma once
#include "cocos2d.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentCookie : public HexusOpponentData
{
public:
	static HexusOpponentCookie* getInstance();

private:
	HexusOpponentCookie();
	~HexusOpponentCookie();

	static const std::string OpponentSaveKey;
	static HexusOpponentCookie* instance;
};
