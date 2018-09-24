#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentJunglePirate : public HexusOpponentData
{
public:
	static HexusOpponentJunglePirate* getInstance();

private:
	HexusOpponentJunglePirate();
	~HexusOpponentJunglePirate();

	static const std::string StringKeyOpponentName;
	static HexusOpponentJunglePirate* instance;
};
