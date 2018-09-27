#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentJungleMinotaur : public HexusOpponentData
{
public:
	static HexusOpponentJungleMinotaur* getInstance();

private:
	HexusOpponentJungleMinotaur();
	~HexusOpponentJungleMinotaur();

	static const std::string StringKeyOpponentName;
	static HexusOpponentJungleMinotaur* instance;
};
