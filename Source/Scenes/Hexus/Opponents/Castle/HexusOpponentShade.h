#pragma once
#include "cocos2d.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentShade : public HexusOpponentData
{
public:
	static HexusOpponentShade* getInstance();

private:
	HexusOpponentShade();
	~HexusOpponentShade();

	static const std::string OpponentSaveKey;
	static HexusOpponentShade* instance;
};
