#pragma once
#include "cocos2d.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentPan : public HexusOpponentData
{
public:
	static HexusOpponentPan* getInstance();

private:
	HexusOpponentPan();
	~HexusOpponentPan();

	static const std::string OpponentSaveKey;
	static HexusOpponentPan* instance;
};
