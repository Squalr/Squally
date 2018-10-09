#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentForestViking : public HexusOpponentData
{
public:
	static HexusOpponentForestViking* getInstance();

private:
	HexusOpponentForestViking();
	~HexusOpponentForestViking();

	static const std::string StringKeyOpponentName;
	static HexusOpponentForestViking* instance;
};
