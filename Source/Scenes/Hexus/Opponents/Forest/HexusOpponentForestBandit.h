#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentForestBandit : public HexusOpponentData
{
public:
	static HexusOpponentForestBandit* getInstance();

private:
	HexusOpponentForestBandit();
	~HexusOpponentForestBandit();

	static const std::string StringKeyOpponentName;
	static HexusOpponentForestBandit* instance;
};
