#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentThion : public HexusOpponentData
{
public:
	static HexusOpponentThion* getInstance();

private:
	HexusOpponentThion();
	~HexusOpponentThion();

	static const std::string StringKeyOpponentName;
	static HexusOpponentThion* instance;
};
