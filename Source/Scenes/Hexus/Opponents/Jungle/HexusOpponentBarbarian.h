#pragma once
#include "cocos2d.h"

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentBarbarian : public HexusOpponentData
{
public:
	static HexusOpponentBarbarian* getInstance();

private:
	HexusOpponentBarbarian();
	~HexusOpponentBarbarian();

	static const std::string OpponentSaveKey;
	static HexusOpponentBarbarian* instance;
};
