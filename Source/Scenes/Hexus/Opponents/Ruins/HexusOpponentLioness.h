#pragma once
#include "cocos2d.h"

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentLioness : public HexusOpponentData
{
public:
	static HexusOpponentLioness* getInstance();

private:
	HexusOpponentLioness();
	~HexusOpponentLioness();

	static const std::string OpponentSaveKey;
	static HexusOpponentLioness* instance;
};
