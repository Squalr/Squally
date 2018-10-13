#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentLightningGolem : public HexusOpponentData
{
public:
	static HexusOpponentLightningGolem* getInstance();

private:
	HexusOpponentLightningGolem();
	~HexusOpponentLightningGolem();

	static const std::string StringKeyOpponentName;
	static HexusOpponentLightningGolem* instance;
};
