#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentRuinsLionMan : public HexusOpponentData
{
public:
	static HexusOpponentRuinsLionMan* getInstance();

private:
	HexusOpponentRuinsLionMan();
	~HexusOpponentRuinsLionMan();

	static const std::string StringKeyOpponentName;
	static HexusOpponentRuinsLionMan* instance;
};
