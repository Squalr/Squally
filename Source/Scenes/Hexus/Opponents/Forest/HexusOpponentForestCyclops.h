#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentForestCyclops : public HexusOpponentData
{
public:
	static HexusOpponentForestCyclops* getInstance();

private:
	HexusOpponentForestCyclops();
	~HexusOpponentForestCyclops();

	static const std::string StringKeyOpponentName;
	static HexusOpponentForestCyclops* instance;
};
