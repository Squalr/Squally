#pragma once
#include "cocos2d.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentRusty : public HexusOpponentData
{
public:
	static HexusOpponentRusty* getInstance();

private:
	HexusOpponentRusty();
	~HexusOpponentRusty();

	static const std::string OpponentSaveKey;
	static HexusOpponentRusty* instance;
};
