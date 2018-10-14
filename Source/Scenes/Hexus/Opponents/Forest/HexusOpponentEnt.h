#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentEnt : public HexusOpponentData
{
public:
	static HexusOpponentEnt* getInstance();

private:
	HexusOpponentEnt();
	~HexusOpponentEnt();

	static const std::string OpponentSaveKey;
	static HexusOpponentEnt* instance;
};
