#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentNecron : public HexusOpponentData
{
public:
	static HexusOpponentNecron* getInstance();

private:
	HexusOpponentNecron();
	~HexusOpponentNecron();

	static const std::string StringKeyOpponentName;
	static HexusOpponentNecron* instance;
};
