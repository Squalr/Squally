#pragma once
#include "cocos2d.h"

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentAbomination : public HexusOpponentData
{
public:
	static HexusOpponentAbomination* getInstance();

private:
	HexusOpponentAbomination();
	~HexusOpponentAbomination();

	static const std::string OpponentSaveKey;
	static HexusOpponentAbomination* instance;
};
