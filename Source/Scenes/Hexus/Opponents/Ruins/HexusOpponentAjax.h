#pragma once
#include "cocos2d.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentAjax : public HexusOpponentData
{
public:
	static HexusOpponentAjax* getInstance();

private:
	HexusOpponentAjax();
	~HexusOpponentAjax();

	static const std::string OpponentSaveKey;
	static HexusOpponentAjax* instance;
};
