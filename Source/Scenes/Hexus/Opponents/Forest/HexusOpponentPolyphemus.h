#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentPolyphemus : public HexusOpponentData
{
public:
	static HexusOpponentPolyphemus* getInstance();

private:
	HexusOpponentPolyphemus();
	~HexusOpponentPolyphemus();

	static const std::string OpponentSaveKey;
	static HexusOpponentPolyphemus* instance;
};
