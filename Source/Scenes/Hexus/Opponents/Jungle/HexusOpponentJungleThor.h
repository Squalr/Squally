#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentJungleThor : public HexusOpponentData
{
public:
	static HexusOpponentJungleThor* getInstance();

private:
	HexusOpponentJungleThor();
	~HexusOpponentJungleThor();

	static const std::string StringKeyOpponentName;
	static HexusOpponentJungleThor* instance;
};
