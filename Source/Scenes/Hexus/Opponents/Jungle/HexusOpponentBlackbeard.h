#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentBlackbeard : public HexusOpponentData
{
public:
	static HexusOpponentBlackbeard* getInstance();

private:
	HexusOpponentBlackbeard();
	~HexusOpponentBlackbeard();

	static const std::string StringKeyOpponentName;
	static HexusOpponentBlackbeard* instance;
};
