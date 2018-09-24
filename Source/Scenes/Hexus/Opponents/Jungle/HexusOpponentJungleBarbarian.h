#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentJungleBarbarian : public HexusOpponentData
{
public:
	static HexusOpponentJungleBarbarian* getInstance();

private:
	HexusOpponentJungleBarbarian();
	~HexusOpponentJungleBarbarian();

	static const std::string StringKeyOpponentName;
	static HexusOpponentJungleBarbarian* instance;
};
