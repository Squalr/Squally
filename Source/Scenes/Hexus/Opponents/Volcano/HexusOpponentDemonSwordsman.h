#pragma once
#include "cocos2d.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentDemonSwordsman : public HexusOpponentData
{
public:
	static HexusOpponentDemonSwordsman* getInstance();

private:
	HexusOpponentDemonSwordsman();
	~HexusOpponentDemonSwordsman();

	static const std::string OpponentSaveKey;
	static HexusOpponentDemonSwordsman* instance;
};
