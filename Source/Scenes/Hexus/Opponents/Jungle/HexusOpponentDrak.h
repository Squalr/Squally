#pragma once
#include "cocos2d.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentDrak : public HexusOpponentData
{
public:
	static HexusOpponentDrak* getInstance();

private:
	HexusOpponentDrak();
	~HexusOpponentDrak();

	static const std::string OpponentSaveKey;
	static HexusOpponentDrak* instance;
};
