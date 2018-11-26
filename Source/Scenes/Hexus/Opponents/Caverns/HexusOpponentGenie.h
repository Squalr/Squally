#pragma once
#include "cocos2d.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentGenie : public HexusOpponentData
{
public:
	static HexusOpponentGenie* getInstance();

private:
	HexusOpponentGenie();
	~HexusOpponentGenie();

	static const std::string OpponentSaveKey;
	static HexusOpponentGenie* instance;
};
