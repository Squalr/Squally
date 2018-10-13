#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentRoger : public HexusOpponentData
{
public:
	static HexusOpponentRoger* getInstance();

private:
	HexusOpponentRoger();
	~HexusOpponentRoger();

	static const std::string StringKeyOpponentName;
	static HexusOpponentRoger* instance;
};
