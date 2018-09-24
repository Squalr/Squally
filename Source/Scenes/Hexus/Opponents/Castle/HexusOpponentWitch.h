#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentWitch : public HexusOpponentData
{
public:
	static HexusOpponentWitch* getInstance();

private:
	HexusOpponentWitch();
	~HexusOpponentWitch();

	static const std::string StringKeyOpponentName;
	static HexusOpponentWitch* instance;
};
