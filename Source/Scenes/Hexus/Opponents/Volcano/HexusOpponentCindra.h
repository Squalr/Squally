#pragma once
#include "cocos2d.h"

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentCindra : public HexusOpponentData
{
public:
	static HexusOpponentCindra* getInstance();

private:
	HexusOpponentCindra();
	~HexusOpponentCindra();

	static const std::string OpponentSaveKey;
	static HexusOpponentCindra* instance;
};
