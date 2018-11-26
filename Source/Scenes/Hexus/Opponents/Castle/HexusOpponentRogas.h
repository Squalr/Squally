#pragma once
#include "cocos2d.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentRogas : public HexusOpponentData
{
public:
	static HexusOpponentRogas* getInstance();

private:
	HexusOpponentRogas();
	~HexusOpponentRogas();

	static const std::string OpponentSaveKey;
	static HexusOpponentRogas* instance;
};
