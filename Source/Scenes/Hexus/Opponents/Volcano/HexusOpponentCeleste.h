#pragma once
#include "cocos2d.h"

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentCeleste : public HexusOpponentData
{
public:
	static HexusOpponentCeleste* getInstance();

private:
	HexusOpponentCeleste();
	~HexusOpponentCeleste();

	static const std::string OpponentSaveKey;
	static HexusOpponentCeleste* instance;
};
