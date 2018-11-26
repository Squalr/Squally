#pragma once
#include "cocos2d.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentJingles : public HexusOpponentData
{
public:
	static HexusOpponentJingles* getInstance();

private:
	HexusOpponentJingles();
	~HexusOpponentJingles();

	static const std::string OpponentSaveKey;
	static HexusOpponentJingles* instance;
};
