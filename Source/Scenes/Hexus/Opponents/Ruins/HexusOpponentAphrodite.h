#pragma once
#include "cocos2d.h"

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentAphrodite : public HexusOpponentData
{
public:
	static HexusOpponentAphrodite* getInstance();

private:
	HexusOpponentAphrodite();
	~HexusOpponentAphrodite();

	static const std::string OpponentSaveKey;
	static HexusOpponentAphrodite* instance;
};
