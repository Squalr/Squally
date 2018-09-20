#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentDataOrcKing : public HexusOpponentData
{
public:
	static HexusOpponentDataOrcKing* getInstance();

private:
	HexusOpponentDataOrcKing();
	~HexusOpponentDataOrcKing();

	static const std::string StringKeyOpponentName;
	static HexusOpponentDataOrcKing* instance;
};
