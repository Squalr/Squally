#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentForestThief : public HexusOpponentData
{
public:
	static HexusOpponentForestThief* getInstance();

private:
	HexusOpponentForestThief();
	~HexusOpponentForestThief();

	static const std::string StringKeyOpponentName;
	static HexusOpponentForestThief* instance;
};
