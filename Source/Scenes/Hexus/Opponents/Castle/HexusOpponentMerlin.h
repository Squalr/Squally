#pragma once
#include "cocos2d.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentMerlin : public HexusOpponentData
{
public:
	static HexusOpponentMerlin* getInstance();

private:
	HexusOpponentMerlin();
	~HexusOpponentMerlin();

	static const std::string OpponentSaveKey;
	static HexusOpponentMerlin* instance;
};
