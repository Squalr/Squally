#pragma once
#include "cocos2d.h"

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentZelina : public HexusOpponentData
{
public:
	static HexusOpponentZelina* getInstance();

private:
	HexusOpponentZelina();
	~HexusOpponentZelina();

	static const std::string OpponentSaveKey;
	static HexusOpponentZelina* instance;
};
