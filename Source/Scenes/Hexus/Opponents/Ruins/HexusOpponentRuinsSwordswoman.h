#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentRuinsSwordswoman : public HexusOpponentData
{
public:
	static HexusOpponentRuinsSwordswoman* getInstance();

private:
	HexusOpponentRuinsSwordswoman();
	~HexusOpponentRuinsSwordswoman();

	static const std::string StringKeyOpponentName;
	static HexusOpponentRuinsSwordswoman* instance;
};
