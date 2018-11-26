#pragma once
#include "cocos2d.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentIrmik : public HexusOpponentData
{
public:
	static HexusOpponentIrmik* getInstance();

private:
	HexusOpponentIrmik();
	~HexusOpponentIrmik();

	static const std::string OpponentSaveKey;
	static HexusOpponentIrmik* instance;
};
