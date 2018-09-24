#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentKnight : public HexusOpponentData
{
public:
	static HexusOpponentKnight* getInstance();

private:
	HexusOpponentKnight();
	~HexusOpponentKnight();

	static const std::string StringKeyOpponentName;
	static HexusOpponentKnight* instance;
};
