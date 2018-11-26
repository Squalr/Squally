#pragma once
#include "cocos2d.h"

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentSarude : public HexusOpponentData
{
public:
	static HexusOpponentSarude* getInstance();

private:
	HexusOpponentSarude();
	~HexusOpponentSarude();

	static const std::string OpponentSaveKey;
	static HexusOpponentSarude* instance;
};
