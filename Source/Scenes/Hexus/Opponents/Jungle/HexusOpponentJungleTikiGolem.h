#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentJungleTikiGolem : public HexusOpponentData
{
public:
	static HexusOpponentJungleTikiGolem* getInstance();

private:
	HexusOpponentJungleTikiGolem();
	~HexusOpponentJungleTikiGolem();

	static const std::string StringKeyOpponentName;
	static HexusOpponentJungleTikiGolem* instance;
};
