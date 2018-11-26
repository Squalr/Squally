#pragma once
#include "cocos2d.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentBodom : public HexusOpponentData
{
public:
	static HexusOpponentBodom* getInstance();

private:
	HexusOpponentBodom();
	~HexusOpponentBodom();

	static const std::string OpponentSaveKey;
	static HexusOpponentBodom* instance;
};
