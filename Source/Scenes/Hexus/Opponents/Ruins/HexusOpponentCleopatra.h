#pragma once
#include "cocos2d.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentCleopatra : public HexusOpponentData
{
public:
	static HexusOpponentCleopatra* getInstance();

private:
	HexusOpponentCleopatra();
	~HexusOpponentCleopatra();

	static const std::string OpponentSaveKey;
	static HexusOpponentCleopatra* instance;
};
