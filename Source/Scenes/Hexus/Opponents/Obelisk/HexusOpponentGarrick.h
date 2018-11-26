#pragma once
#include "cocos2d.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentGarrick : public HexusOpponentData
{
public:
	static HexusOpponentGarrick* getInstance();

private:
	HexusOpponentGarrick();
	~HexusOpponentGarrick();

	static const std::string OpponentSaveKey;
	static HexusOpponentGarrick* instance;
};
