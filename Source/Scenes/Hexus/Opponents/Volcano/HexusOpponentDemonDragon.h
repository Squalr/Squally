#pragma once
#include "cocos2d.h"

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentDemonDragon : public HexusOpponentData
{
public:
	static HexusOpponentDemonDragon* getInstance();

private:
	HexusOpponentDemonDragon();
	~HexusOpponentDemonDragon();

	static const std::string OpponentSaveKey;
	static HexusOpponentDemonDragon* instance;
};
