#pragma once
#include "cocos2d.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentGoblinElf : public HexusOpponentData
{
public:
	static HexusOpponentGoblinElf* getInstance();

private:
	HexusOpponentGoblinElf();
	~HexusOpponentGoblinElf();

	static const std::string OpponentSaveKey;
	static HexusOpponentGoblinElf* instance;
};
