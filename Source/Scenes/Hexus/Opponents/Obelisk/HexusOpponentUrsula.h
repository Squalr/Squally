#pragma once
#include "cocos2d.h"

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentUrsula : public HexusOpponentData
{
public:
	static HexusOpponentUrsula* getInstance();

private:
	HexusOpponentUrsula();
	~HexusOpponentUrsula();

	static const std::string OpponentSaveKey;
	static HexusOpponentUrsula* instance;
};
