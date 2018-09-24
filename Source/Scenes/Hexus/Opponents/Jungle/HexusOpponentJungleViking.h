#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentJungleViking : public HexusOpponentData
{
public:
	static HexusOpponentJungleViking* getInstance();

private:
	HexusOpponentJungleViking();
	~HexusOpponentJungleViking();

	static const std::string StringKeyOpponentName;
	static HexusOpponentJungleViking* instance;
};
