#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentRuinsHorus : public HexusOpponentData
{
public:
	static HexusOpponentRuinsHorus* getInstance();

private:
	HexusOpponentRuinsHorus();
	~HexusOpponentRuinsHorus();

	static const std::string StringKeyOpponentName;
	static HexusOpponentRuinsHorus* instance;
};
