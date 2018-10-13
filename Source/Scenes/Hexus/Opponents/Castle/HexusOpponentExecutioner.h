#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentExecutioner : public HexusOpponentData
{
public:
	static HexusOpponentExecutioner* getInstance();

private:
	HexusOpponentExecutioner();
	~HexusOpponentExecutioner();

	static const std::string StringKeyOpponentName;
	static HexusOpponentExecutioner* instance;
};
