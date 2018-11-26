#pragma once
#include "cocos2d.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentGeryon : public HexusOpponentData
{
public:
	static HexusOpponentGeryon* getInstance();

private:
	HexusOpponentGeryon();
	~HexusOpponentGeryon();

	static const std::string OpponentSaveKey;
	static HexusOpponentGeryon* instance;
};
