#pragma once
#include "cocos2d.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentHera : public HexusOpponentData
{
public:
	static HexusOpponentHera* getInstance();

private:
	HexusOpponentHera();
	~HexusOpponentHera();

	static const std::string OpponentSaveKey;
	static HexusOpponentHera* instance;
};
