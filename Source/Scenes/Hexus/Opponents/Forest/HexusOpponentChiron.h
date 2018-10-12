#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentForestChiron : public HexusOpponentData
{
public:
	static HexusOpponentForestChiron* getInstance();

private:
	HexusOpponentForestChiron();
	~HexusOpponentForestChiron();

	static const std::string StringKeyOpponentName;
	static HexusOpponentForestChiron* instance;
};
