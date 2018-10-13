#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentPrincessMatu : public HexusOpponentData
{
public:
	static HexusOpponentPrincessMatu* getInstance();

private:
	HexusOpponentPrincessMatu();
	~HexusOpponentPrincessMatu();

	static const std::string StringKeyOpponentName;
	static HexusOpponentPrincessMatu* instance;
};
