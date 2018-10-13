#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentDemonSwordsman : public HexusOpponentData
{
public:
	static HexusOpponentDemonSwordsman* getInstance();

private:
	HexusOpponentDemonSwordsman();
	~HexusOpponentDemonSwordsman();

	static const std::string StringKeyOpponentName;
	static HexusOpponentDemonSwordsman* instance;
};
