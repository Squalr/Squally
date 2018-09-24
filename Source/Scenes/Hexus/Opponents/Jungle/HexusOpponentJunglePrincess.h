#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentJunglePrincess : public HexusOpponentData
{
public:
	static HexusOpponentJunglePrincess* getInstance();

private:
	HexusOpponentJunglePrincess();
	~HexusOpponentJunglePrincess();

	static const std::string StringKeyOpponentName;
	static HexusOpponentJunglePrincess* instance;
};
