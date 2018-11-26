#pragma once
#include "cocos2d.h"

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentRaka : public HexusOpponentData
{
public:
	static HexusOpponentRaka* getInstance();

private:
	HexusOpponentRaka();
	~HexusOpponentRaka();

	static const std::string OpponentSaveKey;
	static HexusOpponentRaka* instance;
};
