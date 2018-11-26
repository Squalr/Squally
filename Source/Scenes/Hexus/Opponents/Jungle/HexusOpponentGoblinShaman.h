#pragma once
#include "cocos2d.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentGoblinShaman : public HexusOpponentData
{
public:
	static HexusOpponentGoblinShaman* getInstance();

private:
	HexusOpponentGoblinShaman();
	~HexusOpponentGoblinShaman();

	static const std::string OpponentSaveKey;
	static HexusOpponentGoblinShaman* instance;
};
