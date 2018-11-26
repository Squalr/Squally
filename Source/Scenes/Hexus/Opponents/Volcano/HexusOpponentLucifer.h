#pragma once
#include "cocos2d.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentLucifer : public HexusOpponentData
{
public:
	static HexusOpponentLucifer* getInstance();

private:
	HexusOpponentLucifer();
	~HexusOpponentLucifer();

	static const std::string OpponentSaveKey;
	static HexusOpponentLucifer* instance;
};
