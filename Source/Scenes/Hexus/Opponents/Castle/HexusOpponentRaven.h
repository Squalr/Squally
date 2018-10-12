#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentRaven : public HexusOpponentData
{
public:
	static HexusOpponentRaven* getInstance();

private:
	HexusOpponentRaven();
	~HexusOpponentRaven();

	static const std::string StringKeyOpponentName;
	static HexusOpponentRaven* instance;
};
