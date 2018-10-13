#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentShen : public HexusOpponentData
{
public:
	static HexusOpponentShen* getInstance();

private:
	HexusOpponentShen();
	~HexusOpponentShen();

	static const std::string StringKeyOpponentName;
	static HexusOpponentShen* instance;
};
