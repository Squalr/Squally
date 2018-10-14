#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentScaldor : public HexusOpponentData
{
public:
	static HexusOpponentScaldor* getInstance();

private:
	HexusOpponentScaldor();
	~HexusOpponentScaldor();

	static const std::string OpponentSaveKey;
	static HexusOpponentScaldor* instance;
};
