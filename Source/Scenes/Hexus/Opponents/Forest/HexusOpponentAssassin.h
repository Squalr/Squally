#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentForestAssassin : public HexusOpponentData
{
public:
	static HexusOpponentForestAssassin* getInstance();

private:
	HexusOpponentForestAssassin();
	~HexusOpponentForestAssassin();

	static const std::string StringKeyOpponentName;
	static HexusOpponentForestAssassin* instance;
};
