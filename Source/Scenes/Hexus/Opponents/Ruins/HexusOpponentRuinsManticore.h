#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentRuinsManticore : public HexusOpponentData
{
public:
	static HexusOpponentRuinsManticore* getInstance();

private:
	HexusOpponentRuinsManticore();
	~HexusOpponentRuinsManticore();

	static const std::string StringKeyOpponentName;
	static HexusOpponentRuinsManticore* instance;
};
