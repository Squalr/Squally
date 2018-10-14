#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentZana : public HexusOpponentData
{
public:
	static HexusOpponentZana* getInstance();

private:
	HexusOpponentZana();
	~HexusOpponentZana();

	static const std::string OpponentSaveKey;
	static HexusOpponentZana* instance;
};
