#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentForestArcher : public HexusOpponentData
{
public:
	static HexusOpponentForestArcher* getInstance();

private:
	HexusOpponentForestArcher();
	~HexusOpponentForestArcher();

	static const std::string StringKeyOpponentName;
	static HexusOpponentForestArcher* instance;
};
