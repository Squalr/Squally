#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentForestPolyphemus : public HexusOpponentData
{
public:
	static HexusOpponentForestPolyphemus* getInstance();

private:
	HexusOpponentForestPolyphemus();
	~HexusOpponentForestPolyphemus();

	static const std::string StringKeyOpponentName;
	static HexusOpponentForestPolyphemus* instance;
};
