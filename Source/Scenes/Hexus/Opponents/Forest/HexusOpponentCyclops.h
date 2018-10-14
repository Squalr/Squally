#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentCyclops : public HexusOpponentData
{
public:
	static HexusOpponentCyclops* getInstance();

private:
	HexusOpponentCyclops();
	~HexusOpponentCyclops();

	static const std::string OpponentSaveKey;
	static HexusOpponentCyclops* instance;
};
