#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentJunglePeasant : public HexusOpponentData
{
public:
	static HexusOpponentJunglePeasant* getInstance();

private:
	HexusOpponentJunglePeasant();
	~HexusOpponentJunglePeasant();

	static const std::string StringKeyOpponentName;
	static HexusOpponentJunglePeasant* instance;
};
