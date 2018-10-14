#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentAsh : public HexusOpponentData
{
public:
	static HexusOpponentAsh* getInstance();

private:
	HexusOpponentAsh();
	~HexusOpponentAsh();

	static const std::string OpponentSaveKey;
	static HexusOpponentAsh* instance;
};
