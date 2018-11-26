#pragma once
#include "cocos2d.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentZeus : public HexusOpponentData
{
public:
	static HexusOpponentZeus* getInstance();

private:
	HexusOpponentZeus();
	~HexusOpponentZeus();

	static const std::string OpponentSaveKey;
	static HexusOpponentZeus* instance;
};
