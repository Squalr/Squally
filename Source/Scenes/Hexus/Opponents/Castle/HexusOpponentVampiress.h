#pragma once
#include "cocos2d.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentVampiress : public HexusOpponentData
{
public:
	static HexusOpponentVampiress* getInstance();

private:
	HexusOpponentVampiress();
	~HexusOpponentVampiress();

	static const std::string OpponentSaveKey;
	static HexusOpponentVampiress* instance;
};
