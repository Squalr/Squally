#pragma once
#include "cocos2d.h"

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentForestGolem : public HexusOpponentData
{
public:
	static HexusOpponentForestGolem* getInstance();

private:
	HexusOpponentForestGolem();
	~HexusOpponentForestGolem();

	static const std::string OpponentSaveKey;
	static HexusOpponentForestGolem* instance;
};
