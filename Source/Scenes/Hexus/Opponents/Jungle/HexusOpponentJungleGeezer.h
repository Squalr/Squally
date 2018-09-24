#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentJungleGeezer : public HexusOpponentData
{
public:
	static HexusOpponentJungleGeezer* getInstance();

private:
	HexusOpponentJungleGeezer();
	~HexusOpponentJungleGeezer();

	static const std::string StringKeyOpponentName;
	static HexusOpponentJungleGeezer* instance;
};
