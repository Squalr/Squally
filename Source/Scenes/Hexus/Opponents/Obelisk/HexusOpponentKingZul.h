#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentKingZul : public HexusOpponentData
{
public:
	static HexusOpponentKingZul* getInstance();

private:
	HexusOpponentKingZul();
	~HexusOpponentKingZul();

	static const std::string StringKeyOpponentName;
	static HexusOpponentKingZul* instance;
};
