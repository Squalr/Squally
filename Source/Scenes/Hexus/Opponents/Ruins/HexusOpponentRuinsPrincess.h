#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentRuinsPrincess : public HexusOpponentData
{
public:
	static HexusOpponentRuinsPrincess* getInstance();

private:
	HexusOpponentRuinsPrincess();
	~HexusOpponentRuinsPrincess();

	static const std::string StringKeyOpponentName;
	static HexusOpponentRuinsPrincess* instance;
};
