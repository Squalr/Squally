#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentDataJack : public HexusOpponentData
{
public:
	static HexusOpponentDataJack* getInstance();

private:
	HexusOpponentDataJack();
	~HexusOpponentDataJack();

	static const std::string StringKeyOpponentName;
	static HexusOpponentDataJack* instance;
};
