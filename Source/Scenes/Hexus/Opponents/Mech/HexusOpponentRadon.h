#pragma once
#include "cocos2d.h"

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentRadon : public HexusOpponentData
{
public:
	static HexusOpponentRadon* getInstance();

private:
	HexusOpponentRadon();
	~HexusOpponentRadon();

	static const std::string OpponentSaveKey;
	static HexusOpponentRadon* instance;
};
