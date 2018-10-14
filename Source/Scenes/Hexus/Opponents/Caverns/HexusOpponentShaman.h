#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentShaman : public HexusOpponentData
{
public:
	static HexusOpponentShaman* getInstance();

private:
	HexusOpponentShaman();
	~HexusOpponentShaman();

	static const std::string OpponentSaveKey;
	static HexusOpponentShaman* instance;
};
