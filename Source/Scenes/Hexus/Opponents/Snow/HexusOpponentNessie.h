#pragma once
#include "cocos2d.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentNessie : public HexusOpponentData
{
public:
	static HexusOpponentNessie* getInstance();

private:
	HexusOpponentNessie();
	~HexusOpponentNessie();

	static const std::string OpponentSaveKey;
	static HexusOpponentNessie* instance;
};
