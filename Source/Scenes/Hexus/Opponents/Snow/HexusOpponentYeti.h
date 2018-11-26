#pragma once
#include "cocos2d.h"

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentYeti : public HexusOpponentData
{
public:
	static HexusOpponentYeti* getInstance();

private:
	HexusOpponentYeti();
	~HexusOpponentYeti();

	static const std::string OpponentSaveKey;
	static HexusOpponentYeti* instance;
};
