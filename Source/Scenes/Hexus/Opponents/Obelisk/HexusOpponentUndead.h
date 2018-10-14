#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentUndead : public HexusOpponentData
{
public:
	static HexusOpponentUndead* getInstance();

private:
	HexusOpponentUndead();
	~HexusOpponentUndead();

	static const std::string OpponentSaveKey;
	static HexusOpponentUndead* instance;
};
