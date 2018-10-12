#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentForestDragonOrcKing : public HexusOpponentData
{
public:
	static HexusOpponentForestDragonOrcKing* getInstance();

private:
	HexusOpponentForestDragonOrcKing();
	~HexusOpponentForestDragonOrcKing();

	static const std::string StringKeyOpponentName;
	static HexusOpponentForestDragonOrcKing* instance;
};
