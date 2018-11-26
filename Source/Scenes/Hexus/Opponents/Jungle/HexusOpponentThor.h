#pragma once
#include "cocos2d.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentThor : public HexusOpponentData
{
public:
	static HexusOpponentThor* getInstance();

private:
	HexusOpponentThor();
	~HexusOpponentThor();

	static const std::string OpponentSaveKey;
	static HexusOpponentThor* instance;
};
