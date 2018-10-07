#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentForestPrincess : public HexusOpponentData
{
public:
	static HexusOpponentForestPrincess* getInstance();

private:
	HexusOpponentForestPrincess();
	~HexusOpponentForestPrincess();

	static const std::string StringKeyOpponentName;
	static HexusOpponentForestPrincess* instance;
};
