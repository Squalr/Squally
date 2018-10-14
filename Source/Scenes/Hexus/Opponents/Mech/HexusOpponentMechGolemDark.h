#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentMechGolemDark : public HexusOpponentData
{
public:
	static HexusOpponentMechGolemDark* getInstance();

private:
	HexusOpponentMechGolemDark();
	~HexusOpponentMechGolemDark();

	static const std::string OpponentSaveKey;
	static HexusOpponentMechGolemDark* instance;
};
