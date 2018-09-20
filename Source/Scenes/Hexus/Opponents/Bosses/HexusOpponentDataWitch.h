#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentDataWitch : public HexusOpponentData
{
public:
	static HexusOpponentDataWitch* getInstance();

private:
	HexusOpponentDataWitch();
	~HexusOpponentDataWitch();

	static const std::string StringKeyOpponentName;
	static HexusOpponentDataWitch* instance;
};
