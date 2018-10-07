#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentForestEntMage : public HexusOpponentData
{
public:
	static HexusOpponentForestEntMage* getInstance();

private:
	HexusOpponentForestEntMage();
	~HexusOpponentForestEntMage();

	static const std::string StringKeyOpponentName;
	static HexusOpponentForestEntMage* instance;
};
