#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentRuinsLioness : public HexusOpponentData
{
public:
	static HexusOpponentRuinsLioness* getInstance();

private:
	HexusOpponentRuinsLioness();
	~HexusOpponentRuinsLioness();

	static const std::string StringKeyOpponentName;
	static HexusOpponentRuinsLioness* instance;
};
