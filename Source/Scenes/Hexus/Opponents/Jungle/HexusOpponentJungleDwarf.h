#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentJungleDwarf : public HexusOpponentData
{
public:
	static HexusOpponentJungleDwarf* getInstance();

private:
	HexusOpponentJungleDwarf();
	~HexusOpponentJungleDwarf();

	static const std::string StringKeyOpponentName;
	static HexusOpponentJungleDwarf* instance;
};
