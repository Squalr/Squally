#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentCastleSwordswoman : public HexusOpponentData
{
public:
	static HexusOpponentCastleSwordswoman* getInstance();

private:
	HexusOpponentCastleSwordswoman();
	~HexusOpponentCastleSwordswoman();

	static const std::string StringKeyOpponentName;
	static HexusOpponentCastleSwordswoman* instance;
};
