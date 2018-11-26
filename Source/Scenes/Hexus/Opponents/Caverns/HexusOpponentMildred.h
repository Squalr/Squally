#pragma once
#include "cocos2d.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentMildred : public HexusOpponentData
{
public:
	static HexusOpponentMildred* getInstance();

private:
	HexusOpponentMildred();
	~HexusOpponentMildred();

	static const std::string OpponentSaveKey;
	static HexusOpponentMildred* instance;
};
